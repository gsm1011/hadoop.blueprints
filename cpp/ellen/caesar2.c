/*
 *A program that encrypts messages using Caesar's cipher.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {

  // input check, make sure the encryption key has been given 
  // from the command line. 
  if (argc < 2) {
    printf("useage: ./caesar <keyword>");
    return 1; 
  }

  char plaintext[255], ciphertext[255]; 
  char cipherch; 

  /////////////////////////
  // get input from user. 
  /////////////////////////
  // this section will prompt user to enter plain text.
  // I implemented this on myself using the while loop. 
  // You can call the function GetString()?. 
  printf("Please enter your plain text for cipher: ");
  int idx = 0; 
  while (1) {
    char ch = getchar(); 
    
    if(ch == '\n') {
      plaintext[idx++] = '\0'; 
      break;
    }
    plaintext[idx++] = ch; 
    if (idx >= 255) {
      printf("Error, longer than the 255 will be ignored.");
      plaintext[--idx] = '\0';
      break; 
    }
  }

  //plaintext = getString(); // GetString();
  char *keyword = argv[1];
  int keylen = strlen(keyword); 
  int textlen = strlen(plaintext);

  //////////////////////////////////////////
  // do caesar encryption on the plain text.
  ////////////////////////////////////////// 
  // we need to do encryption for each character. 
  // using formula: cihperchar = (plainchar + k) % 26 
  // we need to make sure that the character we are trying
  // to operate on is with in range [0, 25]. 
  // For example, we need to change the letter 'a' to 
  // 'a' - 'a' = 0, and letter 'z' to 'z' - 'a' = 25 etc. 
  int j = 0; // which key to use. 
  for(int i = 0; i < textlen; i++) {
    char ch = plaintext[i];

    char key = keyword[j % keylen]; 
    key = (key >= 'a' && key <= 'z') ? key - 'a' : key -'A';

    //test character within range a-z
    if(ch >= 'a' && ch <= 'z') {
      ciphertext[i] = (ch + key - 'a') % 26 + 'a'; 
      j++;
    }
    
    //test character winthin range A - Z
    else if(ch >= 'A' && ch <= 'Z') {
      ciphertext[i] = (ch + key - 'A') % 26 + 'A';
      j++;
    }

    else 
      ciphertext[i] = ch; 
  }

  // the purpose of this line to end the string. 
  // it is mandatory. 
  ciphertext[textlen] = '\0';

  //////////////////////////
  // Output. 
  //////////////////////////
    
  printf("Plain text is: %s\n", plaintext); //print output
  printf("Cipher text is: %s\n", ciphertext);

  return 0; 
}
