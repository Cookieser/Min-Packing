#include "seal-part/examples.h"
#include <gmp.h>
#include <string>
#include <time.h>
#include "coding/encoding.h"
#include "coding/decoding.h"
#include "paillier/lsic.h"

#include "paillier/paillier.h"

#include "paillier/encrypted_comparing.h"
using namespace std;
using namespace seal;


int valueAtBit(int num, int bit) {

    return (num >> (bit -1)) & 1;

}

vector<uint64_t> seal_lsic(mpz_t a, mpz_t b,int n,int block,int l)
{
	cout<<"------------------------LSIC------------------------"<<"\n"<<endl;


	mpz_t res;

	mpz_inits(res,NULL);
	
   
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
    //cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;
    


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
    
	
	
	
    // Data
    

    BatchEncoder batch_encoder(context);
    size_t slot_count = batch_encoder.slot_count();
    size_t row_size = slot_count / 2;
    //cout << "Plaintext matrix row size: " << row_size << endl;
    
    
    int *value_a=testDecoding(a, l, block, n);
    int *value_b=testDecoding(b, l, block, n);
    int encoding_row=(n+1)/2;
    
    
    vector<uint64_t> matrix_a(slot_count, 0ULL);
   
    for(int i=0; i<encoding_row;i++){
    matrix_a[i]=value_a[i];
    }
    for(int i=0; i<n-encoding_row;i++){
    matrix_a[row_size + i]=value_a[encoding_row+ i];
    }
     //cout << "matrix_a:" << endl;
    print_matrix(matrix_a, row_size);
    
    
    vector<uint64_t> matrix_b(slot_count, 0ULL);
   
    for(int i=0; i<encoding_row;i++){
    matrix_b[i]=value_b[i];
    }
    for(int i=0; i<n-encoding_row;i++){
    matrix_b[row_size + i]=value_b[encoding_row+ i];
    }
     //cout << "matrix_b:" << endl;
    print_matrix(matrix_b, row_size);
    

   
    
    
    //a0
    vector<uint64_t> matrix_a0(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_a0[i]=(valueAtBit(matrix_a[i],1));
    matrix_a0[row_size + i]=(valueAtBit(matrix_a[row_size + i],1));
    }
     //cout << "matrix_a0:" << endl;
    //print_matrix(matrix_a0, row_size);
    
    //b0
    vector<uint64_t> matrix_b0(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_b0[i]=(valueAtBit(matrix_b[i],1));
    matrix_b0[row_size + i]=(valueAtBit(matrix_b[row_size + i],1));
    }
    // cout << "matrix_b0:" << endl;
    //print_matrix(matrix_b0, row_size);
    Plaintext plain_matrix_b0;
    batch_encoder.encode(matrix_b0, plain_matrix_b0);
    Ciphertext encrypted_matrix_b0;
    encryptor.encrypt(plain_matrix_b0, encrypted_matrix_b0);
    
    
    
    
    //1-a0
    vector<uint64_t> matrix_one_sub_a0(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_one_sub_a0[i]=1-matrix_a0[i];
    matrix_one_sub_a0[row_size + i]=1-matrix_a0[row_size + i];
    }
    // cout << "matrix_one_sub_a0:" << endl;
    //print_matrix(matrix_one_sub_a0, row_size);
    Plaintext plain_matrix_one_sub_a0;
    batch_encoder.encode(matrix_one_sub_a0, plain_matrix_one_sub_a0);
    Ciphertext encrypted_matrix_one_sub_a0;
    encryptor.encrypt(plain_matrix_one_sub_a0, encrypted_matrix_one_sub_a0);
    
    
    
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
    
    vector<uint64_t> matrix_zero(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_one[i]=0;
    matrix_one[row_size + i]=0;
    }
    // cout << "matrix_zero:" << endl;
    //print_matrix(matrix_zero, row_size);
    Plaintext zero_plain;
    batch_encoder.encode(matrix_zero, zero_plain);
    Ciphertext zero_encrypted;
    encryptor.encrypt(zero_plain, zero_encrypted);
    
    
    
    //t= b0*(1-a0)
    
    Ciphertext t_encrypted;
    evaluator.multiply(encrypted_matrix_b0,encrypted_matrix_one_sub_a0,t_encrypted);
    evaluator.relinearize_inplace(t_encrypted, relin_keys);
    
    Plaintext plain_result;

    decryptor.decrypt(t_encrypted, plain_result);
    vector<uint64_t> pod_result;
    batch_encoder.decode(plain_result, pod_result);
    //cout << "t:" << endl;
    //print_matrix(pod_result, row_size);
    
    
    for(int i=2;i<l+1;i++){
    	srand((unsigned)time(NULL));
    
    
	//tau=t*(1-c)+(1-t)*c
    	//c
    	vector<uint64_t> matrix_c(slot_count, 0ULL);    
    	for(int j=0; j<row_size;j++){
    		matrix_c[j]=rand()%2;
    		matrix_c[row_size + j]=rand()%2;
    	}
    	// cout << "matrix_c:" << endl;
    	//print_matrix(matrix_c, row_size);
    	Plaintext c_plain;
    	batch_encoder.encode(matrix_c, c_plain);
    
    	Ciphertext c_encrypted;
    	encryptor.encrypt(c_plain, c_encrypted);
    
    
    
    
    	//1-c
    	vector<uint64_t> matrix_one_sub_c(slot_count, 0ULL);    
    	for(int j=0; j<row_size;j++){
    		matrix_one_sub_c[j]=1-matrix_c[j];
    		matrix_one_sub_c[row_size + j]=1-matrix_c[row_size + j];
    	}
    	// cout << "matrix_one_sub_c:" << endl;
    	//print_matrix(matrix_one_sub_c, row_size);
    	Plaintext one_sub_c_plain;
    	batch_encoder.encode(matrix_one_sub_c, one_sub_c_plain);
    
    	Ciphertext one_sub_c_encrypted;
    	encryptor.encrypt(one_sub_c_plain, one_sub_c_encrypted);
    
    	//1-t
    	Ciphertext one_sub_t_encrypted;
    	evaluator.sub(one_encrypted,t_encrypted,one_sub_t_encrypted);
   

    	Ciphertext resa_encrypted;
    	Ciphertext resb_encrypted;
    	evaluator.multiply(t_encrypted,one_sub_c_encrypted,resa_encrypted);
    	evaluator.relinearize_inplace(resa_encrypted, relin_keys);
    
    	evaluator.multiply(one_sub_t_encrypted,c_encrypted,resb_encrypted);
    	evaluator.relinearize_inplace(resb_encrypted, relin_keys);
    
    	Ciphertext tau_encrypted;
    	evaluator.add(resa_encrypted,resb_encrypted,tau_encrypted);
    
    
    
    	//decryptor.decrypt(tau_encrypted, plain_result);
    	//batch_encoder.decode(plain_result, pod_result);
    	//cout << "tau:" << endl;
    	//print_matrix(pod_result, row_size);
    
    
    	// randomizes 
    	Plaintext tau_decrypted;
    	decryptor.decrypt(tau_encrypted, tau_decrypted);
  
    	encryptor.encrypt(tau_decrypted, tau_encrypted);
    	//decryptor.decrypt(tau_encrypted, plain_result);
    	//batch_encoder.decode(plain_result, pod_result);
    	//cout << "re-tau:" << endl;
    	//print_matrix(pod_result, row_size);
   
    
    
    	//tb=bi*tau
    
    	//bi
    	cout<<i<<endl; 
    	vector<uint64_t> matrix_bi(slot_count, 0ULL);    
    	for(int j=0; j<row_size;j++){
    		matrix_bi[j]=(valueAtBit(matrix_b[j],i));
    		matrix_bi[row_size + j]=(valueAtBit(matrix_b[row_size + j],i));
    	}
     	//cout << "matrix_bi:" << endl;
    	//print_matrix(matrix_bi, row_size);
    	Plaintext bi_plain;
    	batch_encoder.encode(matrix_bi, bi_plain);
    	Ciphertext bi_encrypted;
    	encryptor.encrypt(bi_plain, bi_encrypted);
    
    
    	Ciphertext tb_encrypted;
    	evaluator.multiply(tau_encrypted, bi_encrypted,tb_encrypted);
    	evaluator.relinearize_inplace(tb_encrypted, relin_keys);
    	//decryptor.decrypt(tb_encrypted, plain_result);
    	//batch_encoder.decode(plain_result, pod_result);
    	//cout << "tb:" << endl;
    	//print_matrix(pod_result, row_size);
    
    	//tb=(bi-tb)*(c)+(1-c)*tb
    	Ciphertext resc_encrypted;
    	evaluator.sub(bi_encrypted,tb_encrypted,resc_encrypted);
    	evaluator.multiply(resc_encrypted, c_encrypted,resc_encrypted);
    	evaluator.relinearize_inplace(resc_encrypted, relin_keys);
    	Ciphertext resd_encrypted;
    	evaluator.multiply(tb_encrypted,one_sub_c_encrypted,resd_encrypted);
    	evaluator.relinearize_inplace(resd_encrypted, relin_keys);
    	evaluator.add(resc_encrypted,resd_encrypted,tb_encrypted);
    
    	//decryptor.decrypt(tb_encrypted, plain_result);
    	//batch_encoder.decode(plain_result, pod_result);
    	//cout << "tb:" << endl;
    	//print_matrix(pod_result, row_size);
    
    	//t=(t+bi-tb)(1-ai)+tb*ai
    
    	//ai
    	vector<uint64_t> matrix_ai(slot_count, 0ULL);  
    	cout<<i<<endl;  
    	for(int j=0; j<row_size;j++){
    		matrix_ai[j]=(valueAtBit(matrix_a[j],i));
    		matrix_ai[row_size + j]=(valueAtBit(matrix_a[row_size + j],i));
    	}
    	// cout << "matrix_ai:" << endl;
    	//print_matrix(matrix_ai, row_size);
    	Plaintext ai_plain;
    	batch_encoder.encode(matrix_ai, ai_plain);
    	Ciphertext ai_encrypted;
    	encryptor.encrypt(ai_plain, ai_encrypted);
    
    	//1-ai
    	vector<uint64_t> matrix_one_sub_ai(slot_count, 0ULL);    
    	for(int j=0; j<row_size;j++){
    		matrix_one_sub_ai[j]=1-matrix_ai[j];
    		matrix_one_sub_ai[row_size + j]=1-matrix_ai[row_size + j];
    	}
    	// cout << "matrix_one_sub_ai:" << endl;
    	//print_matrix(matrix_one_sub_ai, row_size);
    	Plaintext one_sub_ai_plain;
    	batch_encoder.encode(matrix_one_sub_ai, one_sub_ai_plain);
    
    	Ciphertext one_sub_ai_encrypted;
    	encryptor.encrypt(one_sub_ai_plain, one_sub_ai_encrypted);
    
    	Ciphertext rese_encrypted;
    	evaluator.add(bi_encrypted,t_encrypted,t_encrypted);
    	evaluator.sub(t_encrypted,tb_encrypted,t_encrypted);
    	evaluator.multiply(t_encrypted,one_sub_ai_encrypted,rese_encrypted);
    	evaluator.relinearize_inplace(rese_encrypted, relin_keys);
     	//decryptor.decrypt(rese_encrypted, plain_result);
    	//batch_encoder.decode(plain_result, pod_result);
    	//cout << "res e:" << endl;
    	//print_matrix(pod_result, row_size);
    
    	Ciphertext resf_encrypted;
    	evaluator.multiply(tb_encrypted,ai_encrypted,resf_encrypted);
    	evaluator.relinearize_inplace(resf_encrypted, relin_keys);
    	//decryptor.decrypt(resf_encrypted, plain_result);
   	//batch_encoder.decode(plain_result, pod_result);
    	//cout << "res e:" << endl;
    	//print_matrix(pod_result, row_size);
    
    
    	evaluator.add(rese_encrypted,resf_encrypted,t_encrypted);
    	evaluator.relinearize_inplace(t_encrypted, relin_keys);
    	decryptor.decrypt(t_encrypted, plain_result);
    	batch_encoder.decode(plain_result, pod_result);
    	cout << "t:" << endl;
    	print_matrix(pod_result, row_size);
    
    
    	cout << "    + size of freshly encrypted t: " << t_encrypted.size() << endl;

    
    	cout << "    + noise budget in freshly encrypted t: " << decryptor.invariant_noise_budget(t_encrypted) << " bits"
         << endl;
    	cout<<"-------------------"<<endl;
    
    
    	
    
    }
    

    
    
 
	mpz_clear(res);
   
    	return pod_result;
} 
