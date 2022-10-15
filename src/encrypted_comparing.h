

#ifndef ENCRYPTED_COMPARING_H_
#define ENCRYPTED_COMPARING_H_


#include <stdio.h>
#include <gmp.h>
#include "../include/paillier.h"
#include "lsic.h"







#ifdef PAILLIER_DEBUG
/** Print debug message
 *
 * @ingroup Tools
 */
#define DEBUG_MSG(str) fputs(str, stderr)
#else
#define DEBUG_MSG(str)
#endif
int encrypted_comparing(mpz_t res,mpz_t ca,mpz_t cb,int l,paillier_public_key pub,paillier_private_key priv);




#endif 
