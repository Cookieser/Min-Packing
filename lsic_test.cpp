#include <gmp.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>


#include "seal_lsic.cpp"
using namespace std;
using namespace seal;




int main(){


int l=7;

/*	parms   */
    EncryptionParameters parms(scheme_type::bfv);

    
    size_t poly_modulus_degree = 16384 ;
    parms.set_poly_modulus_degree(poly_modulus_degree);

    
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));

    
    parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 20));

    
    SEALContext context(parms);
    
    print_parameters(context);
    cout << endl; 

  KeyGenerator keygen(context);

	SecretKey secret_key = keygen.secret_key();
    
    PublicKey public_key;
    
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);
    
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);

    Evaluator evaluator(context);
   

    Decryptor decryptor(context, secret_key);
    auto qualifiers = context.first_context_data()->qualifiers();
    cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;
    
    
     BatchEncoder batch_encoder(context);
    size_t slot_count = batch_encoder.slot_count();
    size_t row_size = slot_count / 2;
    cout << "Plaintext matrix row size: " << row_size << endl;
    
    vector<uint64_t> matrix_a(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_a[i]=10;
    matrix_a[row_size + i]=10;
    }
    cout << "matrix_a:" << endl;
    print_matrix(matrix_a, row_size);
    Plaintext a_plain;
    batch_encoder.encode(matrix_a, a_plain);
    Ciphertext a_encrypted;
    encryptor.encrypt(a_plain, a_encrypted);
    
       vector<uint64_t> matrix_b(slot_count, 0ULL);    
    for(int i=0; i<row_size;i++){
    matrix_b[i]=20;
    matrix_b[row_size + i]=20;
    }
    cout << "matrix_b:" << endl;
    print_matrix(matrix_b, row_size);
    Plaintext b_plain;
    batch_encoder.encode(matrix_b, b_plain);
    Ciphertext b_encrypted;
    encryptor.encrypt(b_plain, b_encrypted);
    
    
    vector<uint64_t> matrix_res(slot_count, 0ULL); 
    matrix_res=seal_lsic(a_plain,b_plain,context,secret_key,public_key,relin_keys,7);
    print_matrix(matrix_res, row_size);
/*
    Plaintext res_plain;
    vector<uint64_t> matrix_res(slot_count, 0ULL);
    decryptor.decrypt(res_encrypted, res_plain);
    
    batch_encoder.decode(res_plain, matrix_res);
    cout << "res:" << endl;
    
    */
    
    
    
    return 0;
    }
