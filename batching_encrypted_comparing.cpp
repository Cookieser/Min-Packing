#include "seal-part/examples.h"
#include <gmp.h>
#include <string>
#include <time.h>
#include "coding/encoding.h"
#include "coding/decoding.h"

#include "paillier/lsic.c"
#include "paillier/encrypted_comparing.c"
#include "paillier/paillier.h"
#include "seal_lsic.cpp"

using namespace std;
using namespace seal;

int EncodingLSIC(vector<uint64_t> result,int row_size,int n, int block,int num, mpz_t t) {


	/*
	
	
	1 2         1 2 3                    1   2  3  4  5  6  7  8  9  10
	
	3 4         4 5 6                    11 12 13 14 15 16 17 18 19 20
	
	
	*/
    
	int encoding_row= (num+1)/2;
    
    int base=pow(2, n);
    string m,s;
    char c = '0';
    
    for (int i = 0; i < encoding_row; i++) {
	string q = toBinary(result[i], n);
        
        q.insert(0, block, c);
       
        cout << "Adding value expressed by binary in t :" << q << endl;
       
        
        m = m + q;
   
    }
     for (int i = 0; i < num-encoding_row; i++) {
	string q = toBinary(result[row_size+i], n);
        
        q.insert(0, block, c);
       
        cout << "Adding value expressed by binary in t :" << q << endl;
       
        
        m = m + q;
   
    }

    cout << "The value t packed :" << m << endl;
    printf("%s", "so, the packing value t is ");
    trans(m, t);
    printf("\n");
    
    
    return 0;
}

int EncodingZ(mpz_t z,int n, int block,int num, mpz_t zl,mpz_t d) {


    

    
    int base=pow(2, n);
    string m,s;
    char c = '0';
    int *value=testDecoding(z, n, block, num);
    for (int i = 0; i < num; i++) {
	string q = toBinary(value[i]%base, n);
        string p = toBinary(value[i]/base, n);
        q.insert(0, block, c);
        p.insert(0, block, c);
        cout << "Adding value expressed by binary in d :" << q << endl;
        cout << "Adding value expressed by binary in zl:" << p << endl;
        
        
        m = m + q;
        s = s + p;

    }

    cout << "The value d packed :" << m << endl;
    cout << "The value zl packed:" << s << endl;
    printf("%s", "so, the packing value d is ");
    trans(m, d);
    printf("%s", "so, the packing value zl is ");
    trans(s, zl);
    printf("\n");
    
    
    return 0;
}

int EncodingRandom(int n, int block,int lambda,int num, mpz_t result,mpz_t rl,mpz_t cc) {

    mpz_t r,base;
    
    unsigned long seed = time(NULL);

    mpz_init(result);
    mpz_init(r);
    mpz_init(rl);
    mpz_init(base);
    mpz_init(cc);
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, seed);
    

   
    mpz_set_si(base, pow(2, n));
    string m,s,t;
    char c = '0';
    for (int i = 0; i < num; i++) {
	mpz_urandomb(r,state,n+lambda);
	
	mpz_fdiv_q(rl,r,base);
	mpz_mod (cc, r, base);
	string p = toBinary(mpz_get_ui(rl), n);
        string q = toBinary(mpz_get_ui(r), n+lambda);
        string h = toBinary(mpz_get_ui(cc), n);
        q.insert(0, block-lambda, c);
        p.insert(0, block, c);
        h.insert(0, block, c);
        cout << "Adding value expressed by binary in rl:" << p << endl;
        cout << "Adding value expressed by binary in r :" << q << endl;
        cout << "Adding value expressed by binary in c :" << h << endl;
        
        m = m + q;
        s = s + p;
        t = t + h;

    }

    cout << "The value r packed :" << m << endl;
    cout << "The value rl packed:" << s << endl;
    cout << "The value c packed :" << t << endl;
    printf("%s", "so, the packing value r is ");
    trans(m, result);
    printf("%s", "so, the packing value rl is ");
    trans(s, rl);
    printf("%s", "so, the packing value c is ");
    trans(t, cc);
    printf("\n");
    
    
    mpz_clear(r);
    mpz_clear(base);
    return 0;
}


int EncodingSame(int n, int block, int num, mpz_t result) {

    mpz_init(result);

    int valuemax = pow(2, n) - 1;
    string m;
    char c = '0';
    for (int i = 0; i < num; i++) {
       

        string q = toBinary(pow(2, n), n);
        q.insert(0, block-1, c);
        cout << "Adding value expressed by binary:" << q << endl;
        m = m + q;

    }

    cout << "The value packed:" << m << endl;
    printf("%s", "so, the packing value is ");
    trans(m, result);
    return 0;
}





int batching_encrypted_comparing(mpz_t ca, mpz_t cb,paillier_public_key pub, paillier_private_key priv,int l,int block,int n,int lambda,mpz_t res)
{
 cout<<"\n"<<"\n"<<"batching_encrypted_comparing:......."<<endl;
/*
//generate keys

	    int len=2048;
	    paillier_public_key pub;
	    paillier_private_key priv;

	    paillier_public_init(&pub);
	    paillier_private_init(&priv);
	    paillier_keygen(&pub, &priv, len);
	    
	    
*/	  
	    
	    mpz_t a,b,q,base,change,two,x,cx,cq,negone,r,cr,z,cz,rl,c,d,zl,t,ct,crl,czl,cm,cn,cres;
	    mpz_inits(a,b,q,base,change,two,x,cx,cq,negone,r,cr,res,z,cz,rl,c,d,zl,t,ct,crl,czl,cm,cn,cres,NULL);

           //constant
	    mpz_set_si(two, 2);
	    mpz_set_si(negone, -1);
		
	    
	   
	    	
	   paillier_decrypt(a,ca,&priv);
	   testDecoding(a, l, block, n);
	   paillier_decrypt(b,cb,&priv);
	   testDecoding(b, l, block, n);
	   
	   //encoding q
	   EncodingSame(l,block,n, q);
	   gmp_printf ("q:%Zd\n",q);
	   paillier_encrypt(cq,q,&pub);
	   
	   //[[x]]=[[b-a+q]]
	   paillier_homomorphic_multc(cx,ca,negone,&pub);
	   paillier_homomorphic_add(cx,cb,cx,&pub);
	   paillier_homomorphic_add(cx,cq,cx,&pub);
	   paillier_decrypt(x,cx,&priv);
	   testDecoding(x, l, block, n);
	   
	   
	   //r  rl  c
	   EncodingRandom(l, block,lambda, n, r,rl,c);
	   paillier_encrypt(cr,r,&pub);
	   paillier_encrypt(crl,rl,&pub);
	   
	   //z=x+r  zl  d
	   paillier_homomorphic_add(cz,cx,cr,&pub);
	   paillier_decrypt(z,cz,&priv);
	   EncodingZ(z,l,block,n,zl,d);
	   paillier_encrypt(czl,zl,&pub);
	   
	   //---------------------------------------------------------------------
	 
	 
	 //
	 vector<uint64_t> matrix_c(n, 0ULL);
	  matrix_c=seal_lsic(d, c,n,block,l);
	  EncodingLSIC(matrix_c,16384,l,block,n, t); 
	  gmp_printf ("t:%Zd\n",t);
	 //--------------------------------------------------------------------------  
	/*batching the front x row_size*/
	
	 //t
	 
	 gmp_printf ("t:%Zd\n",t);
	 paillier_encrypt(ct,t,&pub);
	 
	 
	 
	   //z_l-t-r_l
		paillier_homomorphic_multc(cm,ct,negone,&pub);
		paillier_homomorphic_multc(cn,crl,negone,&pub);
	
		paillier_homomorphic_add(cres,czl,cn,&pub);
		paillier_decrypt(res,cres,&priv);
		gmp_printf ("res:%Zd\n",res);
		testDecoding(res, l, block, n);
		
		paillier_homomorphic_add(cres,cres,cm,&pub);
		paillier_decrypt(res,cres,&priv);
		gmp_printf ("res:%Zd\n",res);
		testDecoding(res, l, block, n);
	   
	   
	   
	   
	   mpz_clear(a);
	   mpz_clear(b);
	   mpz_clear(q);
	   mpz_clear(base);
	   mpz_clear(change);
	   mpz_clear(two);
	   mpz_clear(x);
	   mpz_clear(cx);
	   mpz_clear(cq);
	   mpz_clear(negone);
	   mpz_clear(r);
	   mpz_clear(cr);
	   mpz_clear(z);
	   mpz_clear(cz);
	   mpz_clear(rl);
	   mpz_clear(c);
	   mpz_clear(d);
	   mpz_clear(zl);
	   mpz_clear(t);
	   mpz_clear(ct);
	   mpz_clear(crl);
	   mpz_clear(czl);
	   mpz_clear(cm);
	   mpz_clear(cn);
	   mpz_clear(cres);
	  return 0;

    
    
} 
