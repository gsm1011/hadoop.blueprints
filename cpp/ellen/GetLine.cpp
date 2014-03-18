#include<stdio.h> 

int main() {
  const int LEN = 100; 
  char str[LEN];
  char c; 
  int idx = 0; 
  printf("Please enter your string: ");

  while (1) {
    c = getchar(); 
    // printf("%c\n", c);
    str[idx++] = c; 
    if(idx >= LEN) {
      printf("The text you entered is longer than %d, ignored.", LEN); 
      str[--idx] = '\0';
      break; 
    }
    if(c == '\n') {
      str[idx] = '\0';  
      break; 
    }
  }

  printf("The string you entered is: %s\n", str);
}
