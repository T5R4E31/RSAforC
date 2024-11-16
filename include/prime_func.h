#include <stdlib.h>
#include <stdio.h>

typedef struct {
  long long int private_key;
} private_key;

typedef struct {
  long long int mod_chiff;
  long long int exp;
} public_key;

typedef struct {
  private_key pvk;
  public_key pbk;
} all_keys;

int factInterface(int n);
int factRec(int n, int * tab);
int getPrime();
int checkCoprime(int n, int m);
int getCoprime(int n);
long long int modInverse(long long int A, long long int M);
long long int modPow(long long int a, long long int exp, long long int m);
all_keys generateKeys();
long long int * encryptString(char * str, public_key pbk);
char * decryptString(long long int * str, private_key pvk, public_key pbk);
long long int encrypt(long long int a, public_key pbk);
long long int decrypt(long long int a, private_key pvk, public_key pbk);
