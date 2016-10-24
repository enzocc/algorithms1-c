#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int sum(long long *num1, long long *num2, int size, long long* res){
	int i;
	res[0]=*num1 + *num2;

	for(i=1;i<size;i++){
		res[i]=*(num1+i) + *(num2+i)+res[i-1]/100000000;
		res[i-1]=res[i-1]%100000000;		
	}
	res[i]=res[i-1]/100000000;
	res[i-1]=res[i-1]%100000000;

	return 0;
}
int dif(long long *num1, long long *num2, int size, long long *res){
	int i;

	for(i=0;i<size;i++){
		if(num1[i]<num2[i]){
			num1[i+1]=num1[i+1]-1;
			num1[i]=num1[i]+100000000;
		}
		res[i]=num1[i]-num2[i];
	}
	return 0;
}

int prod(long long *num1, long long *num2, int size, long long* res){

	long long resSum1[size],resSum2[size],prod_resSum[2*size], prodLow[size], prodMid[2*size], prodHigh[size];
	long long difTemp[2*size];

	
	if(size==1){
		res[0]=((*num1)*(*num2))%100000000;
		res[1]=((*num1)*(*num2))/100000000;
		printf("Holaa1\n");

		return 0;
	}

	prod(&num1[0],&num2[0],size/2,prodLow); // ---- Low
	printf("ProdLow= %lld - %lld\n",prodLow[1],prodLow[0]);
	prod(&num1[size/2],&num2[size/2],size/2,prodHigh); // ---- High
	printf("ProdHigh= %lld - %lld\n",prodHigh[1],prodHigh[0]);

	sum(&num1[0],&num1[size/2],size/2, resSum1);
	sum(&num2[0],&num2[size/2],size/2, resSum2);
	prod(resSum1,resSum2,2*size,prod_resSum);

	dif(prod_resSum,prodLow,2*size,difTemp);
	dif(difTemp,prodHigh,2*size,prodMid);
	printf("ProdMid= %lld - %lld\n",prodMid[1],prodMid[0]);


	if (size == 2){
		res[0]=prodLow[0];
		res[1]=prodMid[0]+prodLow[1];
		res[2]=prodHigh[0]+prodMid[1]+prodLow[2];
		res[3]=prodHigh[1]+prodMid[2]+prodLow[3];
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	long long a1[2],a2[2],r[4
		];
	int i=0;

	for(i=0;i<2;i++)
		r[i]=0;


	/*a2[0]=66967627;
	a2[1]=99595749;
	a2[2]=24709369;
	a2[3]=62497757;
	a2[4]=74713526;
	a2[5]=23536028;
	a2[6]=28459045;
	a2[7]=27182818;*/
	a2[0]=66967627;
	a2[1]=99595749;
	/*a2[2]=0;
	a2[3]=0;
	a2[4]=0;
	a2[5]=0;
	a2[6]=0;
	a2[7]=0;*/

	/*a1[0]=74944592;
	a1[1]=51058209;
	a1[2]=16939937;
	a1[3]=2884197;
	a1[4]=33832795;
	a1[5]=23846264;
	a1[6]=53589793;
	a1[7]=31415926;*/
	a1[0]=74944592;
	a1[1]=51058209;
	/*a1[2]=0;
	a1[3]=0;
	a1[4]=0;
	a1[5]=0;
	a1[6]=0;
	a1[7]=0;*/

	prod(a1,a2,2,r);

	printf("Final= ");
	for(i=3;i>=0;i--
		)
		printf("%lld\n", r[i]);
	printf("\n");
	return 0;
}