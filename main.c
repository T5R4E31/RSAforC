#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "prime_func.h"

int main(void){
  all_keys keys = generateKeys(); 
  //test for an int
  int val = rand()%10000;
  printf("value : %d\n", val);
  printf("encrypt : %lld\n", encrypt(val, keys.pbk.exp, keys.pbk.mod_chiff));
  printf("decrypt : %lld\n", decrypt(encrypt(val, keys.pbk.exp, keys.pbk.mod_chiff), keys.pvk.private_key, keys.pbk.mod_chiff));
  //test for a string
  char * truc = "Lorem ipsum dolor sit amet, qui minim labore adipisicing minim sint cillum sint consectetur cupidatat.";
  printf("value : %s\n", truc);
  long long int *str_encr = encryptString(truc, keys.pbk);
  printf("encrypt : ");
  for (int i = 0; i<102; i++){
    printf("%x ", (unsigned int)str_encr[i]);
  }
  printf("\n");
  char * str_decr = decryptString(str_encr, keys.pvk, keys.pbk);
  printf("decrypt : %s", str_decr);

  return EXIT_SUCCESS;
}

