#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

#include "api.h"


int main(void)
{
	int k;
        
	// Define the length of the to be signed payload
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
        
	// create reandom message
	for (k = 0; k < mlen; k++) {
             m[k] = ((unsigned char) rand());
	}
	
	// Run for 10 seconds
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

	printf("Signing/s, %f, ", (double)num_sig / tt);
	
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

	printf("Verify/s, %f\n", (double)num_sig / tt);

	return 0;
}
