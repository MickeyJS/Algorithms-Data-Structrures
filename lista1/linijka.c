#include <stdio.h>
int k=1;
void funct(int n){
	if(n > 1) {
		printf("%d still going \n", k);
		k++;
		funct(n/3);
		funct(n/3);
		funct(n/3);
	}
}

int main(){
funct(729);

return 0;
}
