#include <stdio.h>
#include <stdlib.h>
#include <map>

#define LLU unsigned long long int
using namespace std;

int L;

char *myPrint(LLU x){
	char *s = (char *)malloc(sizeof(char)*65);
	for(int i=0; i<L; i++)
		s[L-1-i] = ((x>>i)&1)? '1': '0';
	s[L] = '\0';
	return s;
}

int main(){
	puts("-----Note-----");
	puts("1. The length of the input string can't exceed 64.");
	puts("2. Program will be terminated if recurring or converging (become all 0).");
	puts("----- End-----\n");

	puts("Enter the length of the input string : ");
	fflush(stdout);
	LLU x = 0;
	scanf("%d", &L);

	fflush(stdin);
	puts("Enter the input string (0011...000) : ");
	fflush(stdout);
	char input[65];
	scanf("%s", input);

	// Run
	for(int i=0; i<L; i++)
		if(input[i]=='1')
			x |= ((LLU)1 << (L-1-i));
	
	map<LLU, int> Record;
	map<int, LLU> Reverse;
	int c = 0;
	Record[x] = c;
	Reverse[c] = x;
	while(x != 0){
		LLU tmp = 0;
		for(int i=0; i<L; i++){
			if(!((x>>i)&1)){
				int flag = 0;
				if(i-1>=0 && (x>>(i-1))&1) flag++;
				if(i+1<L  && (x>>(i+1))&1) flag++;
				if(flag == 1) tmp |= ((LLU)1 << i);
			}
		}
		x = tmp;
		c++;
		map<LLU, int>::iterator iter = Record.find(x);
		if(iter == Record.end()) Record[x] = c, Reverse[c] = x;
		else{
			c = iter->second;
			break;
		}
	}
	if(x != 0){
		puts("\n!!! Find Recusion : ");
		map<int, LLU>::iterator iter2 = Reverse.find(c);
		for(; iter2!=Reverse.end(); iter2++)
			printf("%3d => %s\n", iter2->first, myPrint(iter2->second));
	}
	else
		printf("\n!!! Converges at round %d\n", c);
	printf("\nType enter to exit:");
	fflush(stdout);
	fflush(stdin);
	char whatever = getchar();
	return 0;
}
