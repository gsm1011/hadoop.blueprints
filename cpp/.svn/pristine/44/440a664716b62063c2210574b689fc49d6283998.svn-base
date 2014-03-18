#include<iostream> 
#include<string> 
#include<cstdlib>
#include<stdio.h>

using namespace std; 

void usage(); 
string getString(); 
void doCipher(string &, int);

int main(int argc, char** argv) {
  // input check.
  if(argc < 2) {
    usage(); 
    return 1; 
  }
  
  string plainText, cipherText; 

  cout << "please enter your plain text: "; 
  plainText = getString();

  int k = atoi(argv[1]); 

  cipherText = plainText; 
  doCipher(cipherText, k); 

  cout << "Plain Text: " << plainText << endl; 
  cout << "Cipher Text:" << cipherText << endl; 

  return 0; 
}

void usage() {
  cout << "Usage: \n"
       << "\tCaesarCipher <k>" << endl; 
}

string getString() {
  string str; 
  getline(cin, str);
  return str; 
}

void doCipher(string &cipher, int k) {

  int len = cipher.length(); 

  for(int i = 0; i < len; ++i) {
    char base = 'a'; 
    if (cipher[i] >= 'a' && cipher[i] <= 'z') base = 'a'; 
    else if (cipher[i] >= 'A' && cipher[i] <= 'Z') base = 'A'; 
    else base = 0; 

    if (0 != base) {
      cipher[i] = (cipher[i] + k - base) % 26 + base; 
      printf("%d, %c\n", cipher[i], cipher[i]); 
    }
  }
}
