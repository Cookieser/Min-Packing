#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "lsic.h"

#include "encrypted_comparing.h"
#include "../include/paillier.h"


           
int encrypted_comparing(mpz_t res,mpz_t ca,mpz_t cb,int l,paillier_public_key pub,paillier_private_key priv)
{
	/*encrypted Data*/
	
	/*issue:The randaom bit lambda --wrong!!!*/
	
	int lambda=5;
	mpz_t d,tau,t,ct,negone,x,cx,q,cq,r,cr,z,cz,c,base,czl,crl,cm,cn,cres,zl,rl;
	mpz_init(tau);
	mpz_init(ct);
	mpz_init(t);
	mpz_init(x);
	mpz_init(cx);
	mpz_init(q);
	mpz_init(cq);
	mpz_init(r);
	mpz_init(cr);
	mpz_init(z);
	mpz_init(cz);
	mpz_init(c);
	mpz_init(d);
	mpz_init(base);
	mpz_init(negone);
	mpz_init(czl);
	mpz_init(crl);
	mpz_init(cm);
	mpz_init(cn);
	mpz_init(cres);
	mpz_init(zl);
	mpz_init(rl);
	
	
	
	
	
	
	
	    
	    
      //constant
      
      mpz_set_si(negone, -1);
      mpz_set_si(base, 2);
      mpz_pow_ui(q, base, l);
      //gmp_printf ("q:%Zd\n",q);
      paillier_encrypt(cq,q,&pub);
      
      //encrypted Data
	    
	
	// 1-7
	//[[x]]=[[b-a+q]]
	paillier_homomorphic_multc(cx,ca,negone,&pub);
	paillier_homomorphic_add(cx,cb,cx,&pub);
	paillier_homomorphic_add(cx,cq,cx,&pub);
	paillier_decrypt(x,cx,&priv);
	//gmp_printf ("x:%Zd\n",x);
	//mpz_out_str(stdout, 2, x);
	//printf("\n-----------------------the expected res:%d\n",mpz_tstbit(x,l));
	
	
	
	unsigned long seed = time(NULL);
	
	
	
	//r=random(2^{l+lambda}-1)
	gmp_randstate_t state;
	gmp_randinit_default(state);

	gmp_randseed_ui(state, seed);
	mpz_urandomb(r,state,l+lambda);
	paillier_encrypt(cr,r,&pub);
	//gmp_printf ("r:%Zd\n",r);
	//mpz_out_str(stdout, 2, r);
	printf("\n");
	mpz_fdiv_q(rl,r,q);
	
	paillier_encrypt(crl,rl,&pub);
	paillier_decrypt(rl,crl,&priv);
	//gmp_printf ("rl:%Zd\n",rl);

	//printf("\n");
	
	
	//[[z]]=[[x+r]]
	paillier_homomorphic_add(cz,cx,cr,&pub);
	paillier_decrypt(z,cz,&priv);
	//gmp_printf ("z:%Zd\n",z);
	mpz_fdiv_q(zl,z,q);
	paillier_encrypt(czl,zl,&pub);
	paillier_decrypt(zl,czl,&priv);
	//gmp_printf ("zl:%Zd\n",zl);
	//printf("\n");
	
	//mod
	mpz_mod (c, r, q);
	mpz_mod (d, z, q);
	//mpz_out_str(stdout, 2, c);
	

	//gmp_printf ("c:%Zd\n",c);
	//gmp_printf ("d:%Zd\n",d);
	
	
	    
	//LSIC     t=1  
	LSIC(d,c,l,ct,pub,priv);
	//mpz_set_si(t, 1);
	
	//paillier_encrypt(ct,t,&pub);
	paillier_decrypt(t,ct,&priv);
	//gmp_printf ("t:%Zd\n",t);
	
	
	
	//z_l-t-r_l
	paillier_homomorphic_multc(cm,ct,negone,&pub);
	paillier_homomorphic_multc(cn,crl,negone,&pub);
	
	paillier_homomorphic_add(cres,czl,cm,&pub);
	paillier_homomorphic_add(cres,cres,cn,&pub);
	
	paillier_decrypt(res,cres,&priv);
	//gmp_printf ("finial:%Zd\n",res);
	printf("----------------------------encrypted_comparing:");
	if(!mpz_cmp_si(res,0)) printf("A>B\n");
	else printf("A<=B\n");
	
	
	    

 
	mpz_clear(d);

	mpz_clear(tau);
	mpz_clear(ct);
	mpz_clear(negone);
	mpz_clear(x);
	mpz_clear(cx);
	mpz_clear(q);
	mpz_clear(cq);
	mpz_clear(r);
	mpz_clear(cr);
	mpz_clear(z);
	mpz_clear(cz);
	mpz_clear(c);
	mpz_clear(czl);
	mpz_clear(crl);
	mpz_clear(cm);	
	mpz_clear(cn);	 	
	mpz_clear(t);  
	mpz_clear(base); 
	mpz_clear(cres);   
	mpz_clear(zl); 
	mpz_clear(rl); 
	    
        return 0;



}
