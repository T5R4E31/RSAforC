#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//max value of primes
// /!\ slows down the program if upped
#define MAX_INT 1000

//define private and public key struct
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

//get a prime number, iterative
int getPrime(){
  int n = rand()%MAX_INT;
  for (int i = 2; i*i<MAX_INT; i++){
    if (!(n%i)){
      n = rand()%MAX_INT;
      i = 1;
    }
  }
  return n;
}

//check if two int are coprimes
int checkCoprime(int n, int m){
  for (int i = 2; i<(n < m ? n: m); i++){
    if (!(n%i|m%i)){
      return 0;
    }
  }
  return 1;
}

//get a coprime below n
int getCoprime(int n){
  int i = rand()%n;
  while(!checkCoprime(i, n)){
    i = rand()%n;
  }
  return i;
}

//get the inverse of A mod M
int modInverse(int A, int M){
    long long int m0 = M;
    long long int y = 0;
    long long int x = 1;
    if (M == 1)
        return 0;
    while (A>1) {
        long long int q = A/M;
        long long int t = M;
        M = A%M;
        A = t;
        t = y;
 
        y = x-(q*y);
        x = t;
    }
 
    if (x<0)
        x += m0;
 
    return x;
}

//compute a pow exp mod m using divide and conquer methods
long long int modPow(long long int a, long long exp, long long int m){
  if (a==0) return 0;
  if (exp==0) return 1;
  if (exp%2)
    return ((a%m)*modPow(a, exp-1, m))%m;
  return (modPow(a, exp >> 1, m)*modPow(a, exp >> 1, m))%m;

}

//encrypt function
long long int encrypt(long long int a, public_key pbk){
  return modPow(a, pbk.exp, pbk.mod_chiff);
}

//decrypt function
long long int decrypt(long long int a, private_key pvk, public_key pbk){
  return modPow(a, pvk.private_key, pbk.mod_chiff);
}

//encrypt string function
long long int * encryptString(char * str, public_key pbk){
  long long int * str_encr = malloc(sizeof(long long int)*1000);
  int i = 0;
  while (str[i]!='\0'){
    str_encr[i] = encrypt(str[i], pbk);
    i++;
  }
  return str_encr;
}

//decrypt string function
char * decryptString(long long int * str, private_key pvk, public_key pbk){
  char * str_decr = malloc(sizeof(char) * 1000);
  int i = 0;
  do{
    str_decr[i] = decrypt(str[i], pvk, pbk);
    i++;
  } while (str_decr[i-1]!='\0');
  return str_decr;
}

//generate private and public keys
all_keys generateKeys(){
  srand(time(NULL));
  //get two primes
  int p = getPrime();
  int q = getPrime();

  //compute the product of two primes to get the mod of the public key
  long long int chiff_mod = p*q;
  //compute euler indicator of chiff_mod
  long long int indic_chiff_mod = (p-1)*(q-1);
  //gets a coprime of indic_chiff_mod below it (exponential public key)
  int exp = getCoprime(indic_chiff_mod);
  //gets the modular inverse of exp mod indic_chiff_mod using extended euclidean algorithm
  long long int inv = modInverse(exp, indic_chiff_mod);
 
  //init all keys
  private_key pvk = {inv};
  public_key pbk = {chiff_mod, exp};
  all_keys res = {pvk, pbk};
  return res;
}
