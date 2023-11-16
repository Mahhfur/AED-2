#include <stdio.h>

void fibonacci (int n){
	int i,c=1, m=0, z=1;
	if(n!=0){
	printf("%d ", c);
	for(i=1; i<n; i++){
		printf("%d ", z);
		m=c;
		c=z;
		z=m+c;
	}
	}
}


int main(void) {
	int n;
	scanf("%d", &n);
	fibonacci(n);
  return 0;
}

