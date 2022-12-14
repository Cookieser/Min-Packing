

#ifndef LSIC_H_
#define LSIC_H_


#include <stdio.h>
#include <gmp.h>
#include "paillier.h"








#ifdef PAILLIER_DEBUG
/** Print debug message
 *
 * @ingroup Tools
 */
#define DEBUG_MSG(str) fputs(str, stderr)
#else
#define DEBUG_MSG(str)
#endif
int test(mpz_t ctest,paillier_private_key priv);
int binarybit(mpz_t r,mpz_t val,int n);
int LSIC(mpz_t a,mpz_t b, int l,mpz_t ct,paillier_public_key pub,paillier_private_key priv);




#endif 
