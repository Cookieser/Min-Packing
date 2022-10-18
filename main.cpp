#include<iostream>
#include "coding/encoding.h"
#include "coding/decoding.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>

#include "paillier/lsic.h"
#include "paillier/encrypted_comparing.h"
#include "paillier/paillier.h"
using namespace std;
int main(){



cout<<"hello!"<<endl;
encoding(2,12,"data.txt","m1");
decoding(2,12,4, "m1","output.txt");


//generate keys


           mpz_t pi1,cmax,res;
           mpz_init(res);
	   mpz_init(cmax);
	   mpz_init(pi1);
	    int len=2048;
	    paillier_public_key pub;
	    paillier_private_key priv;

	    paillier_public_init(&pub);
	    paillier_private_init(&priv);
	    paillier_keygen(&pub, &priv, len);
	    
	    int value[5] = {123, 200, 220, 74, 13};
	    mpz_set_si(pi1,value[0]);
	    
	    paillier_encrypt(cmax,pi1,&pub);
	    paillier_decrypt(res,cmax,&priv);
	    gmp_printf ("max:%Zd\n",res);
	    mpz_clear(res);
	   mpz_clear(cmax);
	   mpz_clear(pi1);
	  return 0;



}
