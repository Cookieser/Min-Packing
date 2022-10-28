#include "seal-part/examples.h"
#include <gmp.h>
#include <string>
#include <time.h>
#include <cmath>


#include "seal_lsic.cpp"

using namespace std;
using namespace seal;

vector<uint64_t> seal_encrypted_comparing(Ciphertext a_encrypted, Ciphertext b_encrypted,SEALContext context,SecretKey secret_key,PublicKey public_key,RelinKeys relin_keys,int l,int lambda)
{

    auto qualifiers = context.first_context_data()->qualifiers();
    cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;
    
    
    BatchEncoder batch_encoder(context);
    size_t slot_count = batch_encoder.slot_count();
    size_t row_size = slot_count / 2;
    cout << "Plaintext matrix row size: " << row_size << endl;
    
    
    Encryptor encryptor(context, public_key);

    Evaluator evaluator(context);

    Decryptor decryptor(context, secret_key);
    
    
    
    
    
    //test 
 	Plaintext res_plain;
    vector<uint64_t> pod_res;
    
    //a
    Plaintext a_plain;
    vector<uint64_t> pod_a;
    
    decryptor.decrypt(a_encrypted, a_plain);
    
    batch_encoder.decode(a_plain, pod_a);

    print_matrix(pod_a, row_size);
    
    
    
    //b
    Plaintext b_plain;
    vector<uint64_t> pod_b;
    decryptor.decrypt(b_encrypted, b_plain);
    
    batch_encoder.decode(b_plain, pod_b);

    print_matrix(pod_b, row_size);
    
    int q;
    q= (int)pow(2,l);
    cout<<q<<endl;
    
    //
    //constant
    //q
    vector<uint64_t> matrix_q(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_q[i]=q;
    matrix_q[row_size + i]=q;
    }
    cout << "matrix_q:" << endl;
    print_matrix(matrix_q, row_size);
    Plaintext q_plain;
    batch_encoder.encode(matrix_q, q_plain);
    Ciphertext q_encrypted;
    encryptor.encrypt(q_plain, q_encrypted);
    
    
    //r,c,rl
     srand((int)time(0));
     int ram_max;
     ram_max=(int)pow(2,l+lambda);
    
    vector<uint64_t> matrix_r(slot_count, 0ULL); 
    vector<uint64_t> matrix_c(slot_count, 0ULL);  
    vector<uint64_t> matrix_rl(slot_count, 0ULL);   
    for(int i=0; i<row_size;i++){
    matrix_r[i]=rand()%ram_max;
    matrix_c[i]=matrix_r[i]%q;
    matrix_rl[i]=matrix_r[i]/q;
    matrix_r[row_size + i]=rand()%ram_max;
    matrix_c[row_size + i]=matrix_r[row_size + i]%q;
    matrix_rl[row_size + i]=matrix_r[row_size + i]/q;
    }
    cout << "matrix_r:" << endl;
    print_matrix(matrix_r, row_size);
    Plaintext r_plain;
    batch_encoder.encode(matrix_r, r_plain);
    Ciphertext r_encrypted;
    encryptor.encrypt(r_plain, r_encrypted);
     //c
    cout << "matrix_c:" << endl;
    print_matrix(matrix_c, row_size);
    Plaintext c_plain;
    batch_encoder.encode(matrix_c, c_plain);
    Ciphertext c_encrypted;
    encryptor.encrypt(c_plain, c_encrypted);
    //rl
    cout << "matrix_rl:" << endl;
    print_matrix(matrix_rl, row_size);
    Plaintext rl_plain;
    batch_encoder.encode(matrix_rl, rl_plain);
    Ciphertext rl_encrypted;
    encryptor.encrypt(rl_plain, rl_encrypted);
    
   
    
    
   
    //x=b-a+2^l
    
    Ciphertext x_encrypted;
    evaluator.add(b_encrypted,q_encrypted,x_encrypted);
    evaluator.sub(x_encrypted,a_encrypted,x_encrypted);
     
    decryptor.decrypt(x_encrypted, res_plain);
    
    batch_encoder.decode(res_plain, pod_res);
	
    cout<<"x:"<<endl;
    print_matrix(pod_res, row_size);
    
    
    
     
    
    //z=x+r
    
    Ciphertext z_encrypted;
    evaluator.add(x_encrypted,r_encrypted,z_encrypted);
    
    

    
    
    
    
    //d=z mod 2^l
    
    Plaintext z_plain;
    vector<uint64_t> pod_z;
    decryptor.decrypt(z_encrypted, z_plain);
    batch_encoder.decode(z_plain, pod_z);
    cout<<"z:"<<endl;
    print_matrix(pod_res, row_size);
    
    
    
    vector<uint64_t> matrix_d(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_d[i]=pod_z[i]%q;
    matrix_d[row_size + i]=pod_z[row_size + i]%q;
    }
    cout << "matrix_d:" << endl;
    print_matrix(matrix_d, row_size);
    Plaintext d_plain;
    batch_encoder.encode(matrix_d, d_plain);
    Ciphertext d_encrypted;
    encryptor.encrypt(d_plain, d_encrypted);
    
    
    //zl
    vector<uint64_t> matrix_zl(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_zl[i]=pod_z[i]/q;
    matrix_zl[row_size + i]=pod_z[row_size + i]/q;
    }
    cout << "matrix_zl:" << endl;
    print_matrix(matrix_zl, row_size);
    Plaintext zl_plain;
    batch_encoder.encode(matrix_zl, zl_plain);
    Ciphertext zl_encrypted;
    encryptor.encrypt(zl_plain, zl_encrypted);
    
    
    
    //-------------------------------------------------------------------------------
    //c,d   -------
    /*
    
    for(int i=0; i<row_size;i++){
    	if(matrix_d[i]<matrix_c[i])
    	{
    		matrix_t[i]=1;
    			
	}else
	{
	       matrix_t[i]=0;
	}
    	if(matrix_d[row_size + i]<matrix_c[row_size + i])
    	{
    		matrix_t[row_size + i]=1;
	}else
	{
	
		matrix_t[row_size + i]=0;
	}
    
    
    }
    
     cout << "matrix_t:" << endl;
    
    */
    vector<uint64_t> matrix_t(slot_count, 0ULL); 
    matrix_t=seal_lsic(d_plain,c_plain,context,secret_key,public_key,relin_keys,7);
    print_matrix(matrix_t, row_size);
    Plaintext t_plain;
    batch_encoder.encode(matrix_t, t_plain);
    Ciphertext t_encrypted;
    encryptor.encrypt(t_plain, t_encrypted);
    //---------------------------------------------------------------------------------
    
    
    
    
    
    //t=z/2^l-r/2^l-t

    Ciphertext resa_encrypted;
    evaluator.sub(zl_encrypted,rl_encrypted,resa_encrypted);
    evaluator.sub(resa_encrypted,t_encrypted,t_encrypted);
    
    
    decryptor.decrypt(t_encrypted, res_plain);

    batch_encoder.decode(res_plain, pod_res);
	
    cout<<"t:"<<endl;
    print_matrix(pod_res, row_size);
    
	
    return pod_res;


}
