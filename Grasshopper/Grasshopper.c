#include <stdio.h>
#define ULL unsigned long long int

int Num;

typedef struct {
	ULL a, b; // mean -> a/b
} Grasshopper;

ULL GCD(ULL a, ULL b){
	ULL c;
	while(a != 0){
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

ULL LCM(ULL a, ULL b){
	ULL gcd = GCD(a, b);
	return gcd * (a/gcd) * (b/gcd);
}

Grasshopper Dist(Grasshopper x, Grasshopper y){
	y.a += y.b;
	ULL lcm = LCM(x.b, y.b);
	ULL a = y.a*(lcm/y.b) - x.a*(lcm/x.b);
	ULL b = lcm;
	ULL gcd = GCD(a, b);
	Grasshopper z;
	z.a = a/gcd, z.b = b/gcd;
	if(z.a >= z.b) z.a -= z.b;
	return z;
}

Grasshopper Plus(Grasshopper x, Grasshopper y){
	ULL lcm = LCM(x.b, y.b);
	ULL a = x.a*(lcm/x.b) + y.a*(lcm/y.b);
	ULL b = lcm;
	ULL gcd = GCD(a, b);
	Grasshopper z;
	z.a = a/gcd, z.b = b/gcd;
	return z;
}

// grasshopper x move to the midpoint of x and y.
Grasshopper Move(Grasshopper x, Grasshopper y){
	Grasshopper tmp = Dist(x, y);
	tmp.b *= 2;
	tmp = Plus(x, tmp);
	if(tmp.a >= tmp.b) tmp.a -= tmp.b;
	if(tmp.a == 0) tmp.b = 1;
	return tmp;
}

int main(){
	puts("Note:");
	puts("1: position must less than 1 and be presented by fraction, ex: 1/2.");
	puts("2: 0 must be presented by 0/1.");
	puts("3: Programm will be terminated when grasshopper 0 goes back to 0/1.");
	puts("-----end");

	puts("Enter the number of grasshopper:");
	fflush(stdout);
	scanf("%d", &Num);
	Grasshopper hopper[Num];
	for(int i=0; i<Num; i++){
		printf("Grasshopper %d position :\n", i);
		fflush(stdout);
		scanf("%llu/%llu", &(hopper[i].a), &(hopper[i].b));
	}
	int iteration = 0, flag = 0;
	while(hopper[0].a || !iteration){
		Grasshopper tmpHopper[Num];
		for(int i=0; i<Num; i++)
			tmpHopper[i] = Move(hopper[i], hopper[(i+1)%Num]);
		for(int i=0; i<Num; i++)
			hopper[i].a = tmpHopper[i].a, hopper[i].b = tmpHopper[i].b;

		// Print out
		printf("-----Jump time = %d-----\n", iteration + 1);
		for(int i=0; i<Num; i++)
			printf("%d : %llu/%llu\n", i, hopper[i].a, hopper[i].b);
		printf("--------------------\n");
		fflush(stdout);
		iteration++;
		if(iteration >= 60){
			flag = 1;
			break;
		}
	}

	// Overflow
	if(flag)
		puts("\nOverflow!!!!!\n");
	// Success
	else
		printf("\nSuccess !!!!!\n");
	
	puts("Press enter to exit.");
	fflush(stdin);
	fflush(stdout);
	char stop = getchar();
	return 0;
}
