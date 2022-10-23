#include "seal-part/examples.h"
#include <gmp.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include "coding/encoding.h"

#include "coding/decoding.h"



#include "paillier/paillier.h"

#include "batching_encrypted_comparing.cpp"

using namespace std;
using namespace seal;










vector<uint64_t> decodingMPZ2Vec(int num,int l,int block,int row_size,int slot_count,mpz_t w){
	vector<uint64_t> matrix_bi(slot_count, 0ULL);
	int encoding_row=(num+1)/2;
	int length = (l + block) * num;
    	char *str = new char[100000];
    	string b;
    	char c = '0';

    	mpz_get_str(str, 2, w);
    	b = str;
	
    
    if (b.length() < length) {
        b.insert(0, length - b.length(), c);
    }
    //cout << "The packing result can use binary to express: " << b << endl;


    string val;
    for (int i = 0; i < encoding_row; i++) {
        int a = (l + block) * i;
        int c = block + l;
        val = b.substr(a, c);
        matrix_bi[i] = translittle(val);

    }
    for (int i = encoding_row; i < num; i++) {
        int a = (l + block) * i;
        int c = block + l;
        val = b.substr(a, c);
        matrix_bi[row_size+i-encoding_row] = translittle(val);

    }
    return matrix_bi;


}



int encodingVec(int n,int l,int block,int row_size, vector<uint64_t> max_result, mpz_t result){
	mpz_init(result);
	vector<uint64_t> value(n, 0ULL);
	int encoding_row=(n+1)/2;

	for(int j=0;j<encoding_row;j++)
    	{
    	value[j]=max_result[j];
    	} 
    	for(int j=0;j<n-encoding_row;j++)
    	{
   	value[j+encoding_row]=max_result[row_size + j];
    	
    	} 

    	
    	

    int valuemax = pow(2, l) - 1;
    string m;
    char c = '0';
    for (int i = 0; i < n; i++) {
       
        string q = toBinary(value[i], l);
        q.insert(0, block, c);
       // cout << "Adding value expressed by binary:" << q << endl;
        m = m + q;

    }

    //cout << "The value packed:" << m << endl;
    //printf("%s", "so, the packing value is ");
    trans(m, result);
    return 0;
}





int main(){

/*	parms   */
    EncryptionParameters parms(scheme_type::bfv);

    
    size_t poly_modulus_degree = 16384 ;
    parms.set_poly_modulus_degree(poly_modulus_degree);

    
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));

    
    parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 20));

    
    SEALContext context(parms);
    
    print_parameters(context);
    cout << endl; 

    auto qualifiers = context.first_context_data()->qualifiers();
    cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;

/*	KeyGenerate  */
    KeyGenerator keygen(context);
    
    SecretKey secret_key = keygen.secret_key();
    
    PublicKey public_key;
    
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);
    
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);

    Evaluator evaluator(context);

    Decryptor decryptor(context, secret_key);
    
    
    
    //generate keys
	    int len=2048;
	    paillier_public_key pub;
	    paillier_private_key priv;

	    paillier_public_init(&pub);
	    paillier_private_init(&priv);
	    paillier_keygen(&pub, &priv, len);
    
    
    // Data
    
    Plaintext plain_result;
    vector<uint64_t> pod_result;
    
    int k=4;
    int n=5;
    int nums=k;
    int block=6;
    int l=7;
    int lambda=3;
    
    int value[4][5] = {  
 			{3, 18, 20, 8, 10} ,   
 			{13, 20, 29, 7, 13} ,   
 			{14, 25, 27, 6, 5} ,
 			{14, 22, 23, 12,19 }  
				};
    
    srand((unsigned)time(NULL));
    int q=(int)pow(2,l+lambda);
    
    
    
    
    
    
    //mpz_t
    mpz_t max,cmax,cpii,pii,bi,cbi;
    mpz_inits(max,cmax,cpii,pii,bi,cbi,NULL);
    
    BatchEncoder batch_encoder(context);
    size_t slot_count = batch_encoder.slot_count();
    size_t row_size = slot_count / 2;
    cout << "Plaintext matrix row size: " << row_size << endl;
    
    vector<vector<uint64_t>> matrix;
    int encoding_row=(n+1)/2;
    for(int i=0;i<k;i++){
    vector<uint64_t> matrix_a(slot_count, 0ULL);
    for(int j=0; j<encoding_row;j++){
    matrix_a[j]=value[i][j];
    }
    for(int j=0; j<n-encoding_row;j++){
    matrix_a[row_size + j]=value[i][encoding_row+ j];
    }
    matrix.push_back(matrix_a);
    print_matrix(matrix[i], row_size);
    }
     
     
    //constant
    
    vector<uint64_t> matrix_one(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_one[i]=1;
    matrix_one[row_size + i]=1;
    }
     //cout << "matrix_one:" << endl;
    //print_matrix(matrix_one, row_size);
    Plaintext one_plain;
    batch_encoder.encode(matrix_one, one_plain);
    Ciphertext one_encrypted;
    encryptor.encrypt(one_plain, one_encrypted);
     
    //max:
    Plaintext plain_matrix_max;
    batch_encoder.encode(matrix[0], plain_matrix_max);
    cout << "matrix_max:" << endl;
    
    vector<uint64_t> max_result;
    max_result=matrix[0];
    print_matrix(max_result, row_size);
    
    Ciphertext max_encrypted;
    encryptor.encrypt(plain_matrix_max, max_encrypted);
   for(int i=1; i<k;i++){
    
    
    //apii

     cout << "matrix_apii:" << endl;
    print_matrix(matrix[i], row_size);
    Plaintext apii_plain;
    batch_encoder.encode(matrix[i], apii_plain);
    Ciphertext apii_encrypted;
    encryptor.encrypt(apii_plain, apii_encrypted);
    //------------------------------------------------------------------------------------------
    //transfer
    //FHE:max---max----[[max]]=cmax
    //FHE:pii---pii------[[pi]]=cpi
    
    encodingVec(n,l,block,row_size,max_result,max);
    
    //gmp_printf("%Zd", max);
    paillier_encrypt(cmax,max,&pub);
    
    encodingVec(n,l,block,row_size,matrix[i],pii);
    //gmp_printf("%Zd", pii);
    paillier_encrypt(cpii,pii,&pub);

    
    
    //bi||bi||bi
    batching_encrypted_comparing(cmax, cpii, pub,  priv,l,block,n,lambda,bi);
    gmp_printf ("bi:%Zd\n",bi);
    
    
    //transfer bi--------matrix_bi 
    vector<uint64_t> matrix_bi(slot_count, 0ULL);  
    matrix_bi=decodingMPZ2Vec(n,l,block,row_size,slot_count,bi); 
     cout << "matrix_bi:" << endl;
    print_matrix(matrix_bi, row_size);
    
    
    
    Plaintext bi_plain;
    batch_encoder.encode(matrix_bi, bi_plain);
    Ciphertext bi_encrypted;
    encryptor.encrypt(bi_plain, bi_encrypted);
    
    //1-bi
    Ciphertext one_sub_bi_encrypted;
    evaluator.sub(one_encrypted,bi_encrypted,one_sub_bi_encrypted);
    decryptor.decrypt(one_sub_bi_encrypted, plain_result);
    
    batch_encoder.decode(plain_result, pod_result);
    cout << "1-bi:" << endl;
    print_matrix(pod_result, row_size);
    
    //
    //-------------------------------------------------------------------------------------------
    //ri,si
    
    vector<uint64_t> matrix_ri(slot_count, 0ULL);    
    for(int j=0; j<row_size;j++){
    
    matrix_ri[j]=rand()%q;
    matrix_ri[row_size + j]=rand()%q;
    }
     cout << "matrix_ri:" << endl;
    print_matrix(matrix_ri, row_size);
    Plaintext ri_plain;
    batch_encoder.encode(matrix_ri, ri_plain);
    Ciphertext ri_encrypted;
    encryptor.encrypt(ri_plain, ri_encrypted);
    
    vector<uint64_t> matrix_si(slot_count, 0ULL);    
    for(int j=0; j<row_size;j++){
    
    matrix_si[j]=rand()%q;
    matrix_si[row_size + j]=rand()%q;
    }
     cout << "matrix_si:" << endl;
    print_matrix(matrix_si, row_size);
    Plaintext si_plain;
    batch_encoder.encode(matrix_si, si_plain);
    Ciphertext si_encrypted;
    encryptor.encrypt(si_plain, si_encrypted);
    
    
    //mi=max+ri, ai=apii+si
    Ciphertext mi_encrypted;
    Ciphertext ai_encrypted;
    evaluator.add(max_encrypted,ri_encrypted,mi_encrypted);
    evaluator.add(si_encrypted,apii_encrypted,ai_encrypted);
    
    

    decryptor.decrypt(mi_encrypted, plain_result);
    
    batch_encoder.decode(plain_result, pod_result);
    cout << "mi:" << endl;
    print_matrix(pod_result, row_size);
    
    
    decryptor.decrypt(ai_encrypted, plain_result);
    
    batch_encoder.decode(plain_result, pod_result);
    cout << "ai:" << endl;
    print_matrix(pod_result, row_size);
    
    //vi=bi*ai+(1-bi)*mi
    
    Ciphertext resa_encrypted;
    Ciphertext resb_encrypted;
    evaluator.multiply(bi_encrypted,ai_encrypted,resa_encrypted);
    //evaluator.relinearize_inplace(resa_encrypted, relin_keys);
    
    evaluator.multiply(one_sub_bi_encrypted,mi_encrypted,resb_encrypted);
    //evaluator.relinearize_inplace(resb_encrypted, relin_keys);
    
    Ciphertext vi_encrypted;
    evaluator.add(resa_encrypted,resb_encrypted,vi_encrypted);
    
    decryptor.decrypt(vi_encrypted, plain_result);
    
    batch_encoder.decode(plain_result, pod_result);
    cout << "vi:" << endl;
    print_matrix(pod_result, row_size);
    
    cout << "    + size of freshly encrypted vi: " << vi_encrypted.size() << endl;

    
    cout << "    + noise budget in freshly encrypted vi: " << decryptor.invariant_noise_budget(vi_encrypted) << " bits"
         << endl;
    cout<<"-------------------"<<endl;
    
    //max=vi+(bi-1)*ri-bi*si=vi-(1-bi)*ri-bi*si
    Ciphertext resc_encrypted;
    Ciphertext resd_encrypted;
    evaluator.multiply(bi_encrypted,si_encrypted,resc_encrypted);
    //evaluator.relinearize_inplace(resa_encrypted, relin_keys);
    
    evaluator.multiply(one_sub_bi_encrypted,ri_encrypted,resd_encrypted);
    //evaluator.relinearize_inplace(resb_encrypted, relin_keys);
    evaluator.sub(vi_encrypted,resc_encrypted,vi_encrypted);
    evaluator.sub(vi_encrypted,resd_encrypted,max_encrypted);
    decryptor.decrypt(max_encrypted, plain_matrix_max);
    
    batch_encoder.decode(plain_matrix_max, max_result);
    cout << "max:" << endl;
    print_matrix(max_result, row_size);
    
      cout << "    + size of freshly encrypted max: " << max_encrypted.size() << endl;

    
    cout << "    + noise budget in freshly encrypted max: " << decryptor.invariant_noise_budget(max_encrypted) << " bits"
         << endl;
    cout<<"-------------------"<<endl;
    
    
    
    
    
    
    }
    
     mpz_clear(max);
    mpz_clear(cmax);
    mpz_clear(cpii);
    mpz_clear(pii);
    mpz_clear(bi);
    mpz_clear(cbi);
    
    
}




































