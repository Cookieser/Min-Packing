#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "lsic.h"

#include "encrypted_comparing.h"
#include "../include/paillier.h"


           
int main()
{
	int a = 20;
	int b = 30;
	int l = 10;
	mpz_t res;
	mpz_init(res);
	printf("yes");
	encrypted_comparing(res,a,b,l);
	mpz_clear(res);
        return 0;



}
