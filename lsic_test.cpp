#include "seal_lsic.cpp"
#include "seal-part/examples.h"
#include <gmp.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include "coding/encoding.cpp"



using namespace std;

int main(){

int n=5;
int block=5;
int l=10;
mpz_t a,b;
mpz_inits(a,b,NULL);
int valuea[]={2,31,6,31,9};
int valueb[]={20,30,16,5,19};

testEncoding(valuea, l, block, n, a);
testEncoding(valueb, l, block, n, b);

clock_t start,end;
start = clock();
seal_lsic(a, b,n,block,l);
end = clock();
cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
mpz_clear(a);
mpz_clear(b);

return 0;

}
