#include <stdio.h>
#include <assert.h>

// This program is to compute the permutation of a series of numbers. 

void doPermute(int nums[], int now, int len) {
  if(now == len-1) {

    for(int i = 0; i < len; ++i) {
      printf("%d ", nums[i]);
    }
    printf("\n");

    return; 
  }

  for(int i = now; i < len; ++i) {
    
    int tmp = nums[i]; 
    nums[i] = nums[now]; 
    nums[now] = tmp; 
    doPermute(nums, now+1, len);
  }
}

bool permute(int n) {
  assert(n > 0); 

  int nums[n]; 
  for( int i = 0; i < n; ++i) {
    nums[i] = i; 
  }

  doPermute(nums, 0, n); 
}

int main() {
  permute(4); 

  return 0; 
}
