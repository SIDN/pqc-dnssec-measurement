#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rng.h"
#include "api.h"

#define NB_KATS 10
#define MAX_MARKER_LEN          50

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

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

	uint64_t cycles = 0;
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
