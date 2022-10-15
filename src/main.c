#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "lsic.h"

#include "encrypted_comparing.h"
#include "../include/paillier.h"


int refresh(mpz_t res,mpz_t a,paillier_public_key pub,paillier_private_key priv)
{
	
	
	mpz_t val;
	mpz_init(val);
	paillier_decrypt(val,a,&priv);
	paillier_encrypt(res,val,&pub);
	mpz_clear(val);
	return 0;


}


           
int main()
{
	int l=10;
	int lambda=5;
	int m;
	mpz_t res,cmax,pi1,pii,cpii,cres,bi,ri,si,csi,cri,cmi,cai,cvi,negativeone,cnegativeone,cbi,max,resa,resb,resc,test;
	
	mpz_init(res);
	mpz_init(cmax);
	mpz_init(pi1);
	mpz_init(pii);
	mpz_init(cpii);
	mpz_init(cres);
	mpz_init(bi);
	mpz_init(ri);
	mpz_init(si);
	mpz_init(csi);
	mpz_init(cri);
	mpz_init(cmi);
	mpz_init(cai);
	mpz_init(cvi);
	mpz_init(negativeone);
	mpz_init(cnegativeone);
	mpz_init(cbi);
	mpz_init(max);
	mpz_init(resa);
	mpz_init(resb);
	mpz_init(resc);
	mpz_init(test);
	
//generate keys
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
	    m=1;
	    printf("m=%d\n",m);
	    
	    
	    
	    
	    mpz_set_si(negativeone, -1);
	    paillier_encrypt(cnegativeone,negativeone,&pub);
	    
	    unsigned long seed = time(NULL);
	    
	    	gmp_randstate_t state;
	    	gmp_randinit_default(state);

		gmp_randseed_ui(state, seed);
	    
	    for(int i=1;i<5;i++)
	    {
	    	printf("=======================================================");
	    	mpz_set_si(pii,value[i]);
	    	//gmp_printf ("pii:%Zd\n",pii);
	    	paillier_encrypt(cpii,pii,&pub);
	   
	    	encrypted_comparing(bi,cmax,cpii,l,pub,priv);
	    	//gmp_printf ("bi:%Zd\n",bi);
	    	
	    	
		mpz_urandomb(ri,state,l+lambda);
		//gmp_printf ("ri:%Zd\n",ri);
		paillier_encrypt(cri,ri,&pub);
		mpz_urandomb(si,state,l+lambda);
		//gmp_printf ("si:%Zd\n",si);
		paillier_encrypt(csi,si,&pub);
		
		paillier_homomorphic_add(cmi,cmax,cri,&pub);
		paillier_decrypt(res,cmi,&priv);
		//gmp_printf ("mi:%Zd\n",res);
		
		paillier_homomorphic_add(cai,cpii,csi,&pub);
		paillier_decrypt(res,cai,&priv);
		//gmp_printf ("ai:%Zd\n",res);
		
		
		if(mpz_cmp_si(bi,0))
		{
		// bi=1   [[vi]]=[[ai]]
		m=i+1;

		refresh(cvi,cai,pub,priv);
		paillier_decrypt(res,cvi,&priv);
		//gmp_printf ("vi:%Zd\n",res);
		}
		else
		{
		refresh(cvi,cmi,pub,priv);
		paillier_decrypt(res,cvi,&priv);
		//gmp_printf ("vi:%Zd\n",res);
		}
		
		paillier_encrypt(cbi,bi,&pub);
		//A:max=vi+(bi-1)*ri-bi*si
		
		
		//resa=[[-bi*si]]
		paillier_homomorphic_multc(resa,cbi,si,&pub);
		paillier_decrypt(test,resa,&priv);
		//gmp_printf ("si*bi:%Zd\n",test);
		paillier_homomorphic_multc(resa,resa,negativeone,&pub);
		
		//resb=[[(bi-1)*ri]]
		
		paillier_homomorphic_add(resb,cbi,cnegativeone,&pub);
		paillier_homomorphic_multc(resb,resb,ri,&pub);
		paillier_decrypt(test,resb,&priv);
		//gmp_printf ("resb:%Zd\n",test);
		
		//combine
		paillier_homomorphic_add(cmax,cvi,resa,&pub);

		paillier_homomorphic_add(cmax,cmax,resb,&pub);
		
		paillier_decrypt(max,cmax,&priv);
		printf("m=%d\n",m);
		gmp_printf ("max:%Zd\n",max);
		
		
		printf("=======================================================");
		printf("\n");
		
		
		
		
	    
	    }
	    
	    	
	
	
	

	//
	mpz_clear(res);
	mpz_clear(cmax);
	mpz_clear(pi1);
	mpz_clear(pii);
	mpz_clear(cpii);
	mpz_clear(cres);
	mpz_clear(bi);
	mpz_clear(ri);
	mpz_clear(si);
	mpz_clear(csi);
	mpz_clear(cri);
	mpz_clear(cmi);
	mpz_clear(cai);
	mpz_clear(cvi);
        mpz_clear(negativeone);
        mpz_clear(cnegativeone);
        mpz_clear(cbi);
        mpz_clear(max);
	mpz_clear(resa);
	mpz_clear(resb);
	mpz_clear(resc);
	mpz_clear(test);
        
        
        
        
        
	
	
	
	
	
	
        return 0;



}
