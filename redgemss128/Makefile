LOCAL=/usr/local

HEAD=$(wildcard include/*.h)
SRC=$(wildcard src/*.c)
OBJS=$(SRC:.c=.o)

CC=gcc
# Modify path to point to gf2x and XKCP library
LDFLAGS=-L[PATH-TO-LIB]/gf2x-libs/lib -lgf2x -L[PATH-TO-LIB]XKCP/bin/generic64/ -lkeccak -lcrypto -ldl -lpthread
CFLAGS=-Wall -O4 -march=native -mtune=native -funroll-loops -I include/ -I $(LOCAL)/include -L $(LOCAL)/lib -I[PATH-TO-LIB]/gf2x-libs/include -lgf2x -I [PATH-TO-LIB]/bin/generic64 -lkeccak

all: PQCgenKAT_sign


PQCgenKAT_sign: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<


pqc_dnssec_speedtest: $(OBJS)
	        $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

cleanKAT:
	rm -f PQCsignKAT_*.int PQCsignKAT_*.req PQCsignKAT_*.rsp

clean:
	rm -f PQCgenKAT_sign src/*.o
