CC=    gcc
LD=    gcc


DFLAGS=-D "aligned_alloc(x,y)=malloc(y)"
CFLAGS= -O2 -std=c11 -Wall -Wextra -fno-omit-frame-pointer
INCPATH= -I/usr/local/include -I/opt/local/include -I/usr/include -I$PWD
LDFLAGS=
LIBPATH= -L/usr/local/lib -L/opt/local/lib -L/usr/lib
LIBS=    -lcrypto -lm


ifeq ($(PROJ_DIR),avx2)
	CFLAGS += -mavx2
	CXXFLAGS += -mavx2
endif



SRCS = $(wildcard *.c)
SRCS_O = $(SRCS:.c=.o)
	SRCS_O_ND = $(subst /,,$(SRCS_O))

OBJ = $(SRCS_O_ND)


CSRC= $(wildcard *.c)


pqc_dnssec_speedtest: $(OBJ) pqc_dnssec_speed_test_falcon.o
	        $(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)

%.o: %.c
	        $(CC) $(CFLAGS) $(INCPATH) -c $<

%.o: $(PROJ_DIR)/%.c
	        $(CC) $(CFLAGS) $(INCPATH) -c $<


