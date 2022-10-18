#include "examples.h"
#include <gmp.h>
#include <string>
#include <time.h>

using namespace std;
using namespace seal;



int binarybit(mpz_t r,mpz_t val,int n){
	    mpz_t q, d;
	    mpz_init(q);
            mpz_init(r);
            mpz_init(d);
            mpz_set_si(d, 2);

	    for(int i=0;i<n+1;i++)
        {
		    mpz_fdiv_qr(q,r, val, d);
		    val=q;
        }

           //gmp_printf ("The %d-bit of this value is %Zd\n",n,r);

          mpz_clear(q);
          mpz_clear(d);
          return 0;

}  

int main()
{
   
    /*	parms   */
    EncryptionParameters parms(scheme_type::bfv);

    
    size_t poly_modulus_degree = 4096;
    parms.set_poly_modulus_degree(poly_modulus_degree);

    
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));

    
    parms.set_plain_modulus(1024);

    
    SEALContext context(parms);
    


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
    

    mpz_t a,b;
    mpz_inits(a,b,NULL);
    mpz_set_si(a, 1000);
    mpz_set_si(b, 1000);
    
    //char *str = new char[100000];
    
    //constant
    int l=12;
    Plaintext zero_plain(uint64_to_hex_string(0));
    Ciphertext zero_encrypted;
    encryptor.encrypt(zero_plain, zero_encrypted);
    
    Plaintext one_plain(uint64_to_hex_string(1));
    Ciphertext one_encrypted;
    encryptor.encrypt(one_plain, one_encrypted);
    
    //1-7
    
    
    int a0=mpz_tstbit(a,0);
    printf("a0:%d\n",a0);
    
    int b0=mpz_tstbit(b,0);
    printf("b0:%d\n",b0);
    
    Plaintext b0_plain(uint64_to_hex_string(b0));
    cout << "Express x = " + to_string(b0) + " as a plaintext polynomial 0x" + b0_plain.to_string() + "." << endl;
    
    Ciphertext b0_encrypted;
    encryptor.encrypt(b0_plain, b0_encrypted);


    //cout << "    + size of freshly encrypted b0: " << b0_encrypted.size() << endl;

    
    //cout << "    + noise budget in freshly encrypted b0: " << decryptor.invariant_noise_budget(b0_encrypted) << " bits"
    //     << endl;
     
    
    //Ciphertext
    Ciphertext t_encrypted;  
    
    
   
    
    
    for(int i=1;i<l;i++){
      
    if(a0==0) 
    {
    	
    	t_encrypted=zero_encrypted;
    }else
    {
    t_encrypted=b0_encrypted;
    
    }
    
    
    Plaintext test_decrypted;
    decryptor.decrypt(t_encrypted, test_decrypted);
    //cout << "t:" + test_decrypted.to_string() <<"\n"<< endl;
    
    
    srand((unsigned)time(NULL));
    
    
    //tau=t*(1-c)+(1-t)*c
    
    int c=rand()%2;
    //cout << "c:" <<c<<"\n"<< endl;
    Plaintext c_plain(uint64_to_hex_string(c));
    Ciphertext c_encrypted;
    encryptor.encrypt(c_plain, c_encrypted);
    //cout << "c:" + c_plain.to_string() <<"\n"<< endl;
    
    
    int one_sub_c=1-c;
    Ciphertext one_sub_c_encrypted;
    Plaintext one_sub_c_plain(uint64_to_hex_string(one_sub_c));
    encryptor.encrypt(one_sub_c_plain, one_sub_c_encrypted);
    //cout << "1-c:" + one_sub_c_plain.to_string() <<"\n"<< endl;
    	
    Ciphertext one_sub_t_encrypted;
    evaluator.sub(one_encrypted,t_encrypted,one_sub_t_encrypted);
    decryptor.decrypt(one_sub_t_encrypted, test_decrypted);
    //cout << "1-t:" + test_decrypted.to_string() <<"\n"<< endl;
    
    
    Ciphertext resa_encrypted;
    Ciphertext resb_encrypted;
    evaluator.multiply(t_encrypted,one_sub_c_encrypted,resa_encrypted);
    decryptor.decrypt(resa_encrypted, test_decrypted);
  	//cout << "resa:" + test_decrypted.to_string() <<"\n"<< endl;
    
    evaluator.multiply(one_sub_t_encrypted,c_encrypted,resb_encrypted);
    decryptor.decrypt(resb_encrypted, test_decrypted);
  	//cout << "resb:" + test_decrypted.to_string() <<"\n"<< endl;
    
    Ciphertext tau_encrypted;
    evaluator.add(resa_encrypted,resb_encrypted,tau_encrypted);
    decryptor.decrypt(tau_encrypted, test_decrypted);
    //cout << "tau:" + test_decrypted.to_string() <<"\n"<< endl;
    
    
    
    // randomizes 
    Plaintext tau_decrypted;
    decryptor.decrypt(tau_encrypted, tau_decrypted);
  
    encryptor.encrypt(tau_decrypted, tau_encrypted);
    decryptor.decrypt(tau_encrypted, test_decrypted);
    //cout << "retau:" + test_decrypted.to_string() <<"\n"<< endl;
    
    //tb=bi*tau
    // there is 1--i
    int bi=mpz_tstbit(b,i);
    //printf("bi:%d\n",bi);
    Plaintext bi_plain(uint64_to_hex_string(bi));
    Ciphertext bi_encrypted;
    encryptor.encrypt(bi_plain, bi_encrypted);
    
    Ciphertext tb_encrypted;
    evaluator.multiply(tau_encrypted, bi_encrypted,tb_encrypted);
    decryptor.decrypt(tb_encrypted, test_decrypted);
    //cout << "tb:" + test_decrypted.to_string() <<"\n"<< endl;
    
    //randomizes
    Plaintext tb_decrypted;
    decryptor.decrypt(tb_encrypted, tb_decrypted);
  
    encryptor.encrypt(tb_decrypted, tb_encrypted);
    decryptor.decrypt(tb_encrypted, test_decrypted);
    //cout << "retb:" + test_decrypted.to_string() <<"\n"<< endl;
    
	
	
    //tb=(bi-tb)*(c)+(1-c)*tb
    Ciphertext resc_encrypted;
    evaluator.sub(bi_encrypted,tb_encrypted,resc_encrypted);
    evaluator.multiply(resc_encrypted, c_encrypted,resc_encrypted);
    Ciphertext resd_encrypted;
    evaluator.multiply(tb_encrypted,one_sub_c_encrypted,resd_encrypted);
    evaluator.add(resc_encrypted,resd_encrypted,tb_encrypted);
    decryptor.decrypt(tb_encrypted, test_decrypted);
    //cout << "tb:" + test_decrypted.to_string() <<"\n"<< endl;
    
    
    //t=(t+bi-tb)(1-ai)+tb*ai
    
    int ai=mpz_tstbit(a,i);
    //printf("ai:%d\n",ai);
    Plaintext ai_plain(uint64_to_hex_string(ai));
    Ciphertext ai_encrypted;
    encryptor.encrypt(ai_plain, ai_encrypted);
    
    int one_sub_ai=1-ai;
    //printf("one_sub_ai:%d\n",one_sub_ai);
    Plaintext one_sub_ai_plain(uint64_to_hex_string(one_sub_ai));
    Ciphertext one_sub_ai_encrypted;
    encryptor.encrypt(one_sub_ai_plain, one_sub_ai_encrypted);
    
    Ciphertext rese_encrypted;
    evaluator.add(bi_encrypted,t_encrypted,t_encrypted);
    evaluator.sub(t_encrypted,tb_encrypted,t_encrypted);
    evaluator.multiply(t_encrypted,one_sub_ai_encrypted,rese_encrypted);
    
    Ciphertext resf_encrypted;
    evaluator.multiply(tb_encrypted,ai_encrypted,resf_encrypted);
    evaluator.add(rese_encrypted,resf_encrypted,t_encrypted);
    decryptor.decrypt(t_encrypted, test_decrypted);
    cout << "t:" + test_decrypted.to_string() <<"\n"<< endl;
    
    cout << "    + size of freshly encrypted t: " << t_encrypted.size() << endl;

    
    cout << "    + noise budget in freshly encrypted t: " << decryptor.invariant_noise_budget(t_encrypted) << " bits"
         << endl;
    
    
    //evaluator.relinearize_inplace(t_encrypted, relin_keys);
    // cout << "    + size of freshly encrypted t: " << t_encrypted.size() << endl;

    
    //cout << "    + noise budget in freshly encrypted t: " << decryptor.invariant_noise_budget(t_encrypted) << " bits"
     //    << endl;
	      
            if(test_decrypted.to_string()=="1")
            cout<<"a<b"<<endl;
            else cout<<"a>=b"<<endl;
    		
    		}	
    
 
	
	
    
    
    mpz_clear(a);
    mpz_clear(b);
    return 0;
} 
