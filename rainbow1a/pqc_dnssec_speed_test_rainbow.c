#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "rainbow_config.h"

#include "utils.h"

#include "rng.h"

#include "api.h"

/*
	Tests the execution of the keypair generation, signature generation and signature verification algorithms and prints timing results
*/
int main(void)
{
	int k;
	int mlen = 86;
	unsigned long long smlen;
	unsigned char m[mlen];
	unsigned char m2[mlen];

	unsigned char *sm;
	sm=(unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));
	unsigned char       *pk,*sk;
	pk=(unsigned char*)malloc(CRYPTO_PUBLICKEYBYTES*sizeof(unsigned char));
        sk=(unsigned char*)malloc(CRYPTO_SECRETKEYBYTES*sizeof(unsigned char));

	srand((unsigned int) time(NULL));

        uint64_t num_sig;

        clock_t begin, end;
	begin = clock();
	double tt;

	// create keypair
	crypto_sign_keypair(pk, sk);
	num_sig = 0;
        
//	// create reandom message
	for (k = 0; k < mlen; k++) {
             m[k] = ((unsigned char) rand());
	}
//
	for (;;){ 
		// time signing
		crypto_sign(sm, &smlen, m, (unsigned long long) mlen, sk);
	        end = clock();
		tt = (double)(end - begin) / CLOCKS_PER_SEC;
		num_sig ++;
		if (tt > 10){
		    break;
		}
	}

        //printf("Elapsed Time: %f\n", tt);
	//printf("Signing Counter: %lu\n", num_sig);
	printf("Signing/s, %f, ", (double)num_sig / tt);
//
	tt = 0;
	num_sig = 0;
	for (;;){ 
		// Prepare message
		crypto_sign(sm, &smlen, m, (unsigned long long) mlen, sk);
	        begin = clock();
		// time verifying
	        if (crypto_sign_open(m2, &smlen, sm, smlen, pk) != 0){
			printf("Verification of signature Failed!\n");
    			break; 
		}
	        end = clock();
		tt += (double)(end - begin) / CLOCKS_PER_SEC;
		num_sig ++;
		if (tt > 10){
		    break;
		}
	}

      	//printf("Elapsed Time: %f\n", tt);
	//printf("Verify Counter: %lu\n", num_sig);
	printf("Verify/s, %f\n", (double)num_sig / tt);
//
//	free(pk);
//	free(sk);
//	free(sm);

	return 0;
}
