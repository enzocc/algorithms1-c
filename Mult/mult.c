#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/*int getRealSize(long long *num, int stdsize){
	int i;
	for(i=stdsize-1; i>=0; i--){
		if(num[i]!=0){
			return i+1;
		}
	}
	return 0;
}*/
int sum(long long *num1, long long *num2, int size_inp, long long* ans, int* size_ans){
	int i;
	ans[0]=*num1 + *num2;

	for(i=1;i<size_inp;i++){
		ans[i]=*(num1+i) + *(num2+i)+ans[i-1]/100000000;
		ans[i-1]=ans[i-1]%100000000;		
	}
	ans[i]=ans[i-1]/100000000;
	ans[i-1]=ans[i-1]%100000000;

	if(ans[i] == 0){
		*size_ans = i;
	}
	else
		*size_ans = i+1;	
	return 0;
}
int dif(long long *num1, long long *num2, int size_inp, long long *ans, int* size_ans){
	int i;

	for(i=0;i<size_inp;i++){
		if(num1[i]<num2[i]){
			num1[i+1]=num1[i+1]-1;
			num1[i]=num1[i]+100000000;
		}
		ans[i]=num1[i]-num2[i];
	}

	for(i=size_inp-1;i>=0;i--){
		if(ans[i]!=0){
			*size_ans = i+1;
			return 0;
		}
	}
	*size_ans = 0;
	return 0;
}

int prod(long long *num1, long long *num2, int size_inp, long long* ans, int* size_ans ){

	long long resSum1[size_inp],resSum2[size_inp],prod_resSum[2*size_inp], prodLow[size_inp], prodMid[2*size_inp], prodHigh[size_inp], sumHiLo[2*size_inp];
	long long difTemp[2*size_inp],carry;
	int i,size_prodLow, size_prodHigh, size_prodMid, size_resSum1, size_resSum2, size_prod_resSum, size_sumHiLo;

	for(i=0;i<size_inp;i++){
		resSum1[i]=0;
		resSum2[i]=0;
		prodLow[i]=0;
		prodHigh[i]=0;
		prod_resSum[i]=0;
		prodMid[i]=0;
		sumHiLo[i]=0;
	}
	for(i=size_inp;i<2*size_inp;i++){
		prod_resSum[i]=0;
		prodMid[i]=0;
		sumHiLo[i]=0;
	}

	if(size_inp==1){
		ans[0]=((*num1)*(*num2))%100000000;
		ans[1]=((*num1)*(*num2))/100000000;
		if(ans[1]==0){
			*size_ans = 1;
		}
		else 
			*size_ans = 2;
		return 0;
	}

	prod(&num1[0],&num2[0],size_inp/2,prodLow, &size_prodLow); // ---- Low
	// -----------------------------------
	/*printf("ProdLow(%d)= ",size_prodLow);
	for(i=size_prodLow-1;i>=0;i--){
		printf("%lld ",prodLow[i]);
	}
	printf("\n");*/
	// -----------------------------------
	prod(&num1[size_inp/2],&num2[size_inp/2],size_inp/2,prodHigh,&size_prodHigh); // ---- High
	// -----------------------------------
	/*printf("ProdHigh(%d)= ", size_prodHigh);
	for(i=size_prodHigh-1;i>=0;i--){
		printf("%lld ",prodHigh[i]);
	}
	printf("\n");*/
	// -----------------------------------

	sum(&num1[0],&num1[size_inp/2],size_inp/2, resSum1, &size_resSum1);
	// -----------------------------------
	/*printf("ResSum1(%d)= ", size_resSum1);
	for(i=size_resSum1-1;i>=0;i--){
		printf("%lld ",resSum1[i]);
	}
	printf("\n");*/
	// -----------------------------------
	sum(&num2[0],&num2[size_inp/2],size_inp/2, resSum2, &size_resSum2);
	// -----------------------------------
	printf("ResSum2(%d)= ",size_resSum2);
	/*for(i=size_resSum2-1;i>=0;i--){
		printf("%lld ",resSum2[i]);
	}
	printf("\n");*/
	// -----------------------------------	
	prod(resSum1,resSum2,size_resSum1,prod_resSum, &size_prod_resSum); //We should take the bigger size between resSum1 and resSum2
	// -----------------------------------	
	/*printf("ProdResSum(%d)= ",size_prod_resSum);
	for(i=size_prod_resSum-1;i>=0;i--){
		printf("%lld ",prod_resSum[i]);
	}
	printf("\n");*/
	// -----------------------------------	
	sum(prodLow, prodHigh, size_prodLow, sumHiLo, &size_sumHiLo);
	// -----------------------------------	
	/*printf("SumHiLo(%d)= ",size_sumHiLo);
	for(i=size_sumHiLo-1;i>=0;i--){
		printf("%lld ",sumHiLo[i]);
	}
	printf("\n");*/
	// -----------------------------------	
	dif(prod_resSum, sumHiLo, size_prod_resSum, prodMid,&size_prodMid);
	// -----------------------------------	
	/*printf("ProdMid(%d)= ",size_prodMid);
	for(i=size_prodMid-1;i>=0;i--){
		printf("%lld ",prodMid[i]);
	}
	printf("\n");*/
	// -----------------------------------	
	
	if (size_inp == 2){
		/*printf("================= \n");
		printf("sizeProdLow = %d\n", size_prodLow);
		printf("sizeprodMid = %d\n", size_prodMid);
		printf("sizeProdHigh = %d\n", size_prodHigh);*/
		ans[0]=prodLow[0];
		ans[1]=prodMid[0]+prodLow[1];
		carry=ans[1]/100000000;
		ans[1]=ans[1]%100000000;
		ans[2]=prodHigh[0]+prodMid[1]+carry;
		carry=ans[2]/100000000;
		ans[2]=ans[2]%100000000;
		ans[3]=prodHigh[1]+prodMid[2]+carry;
		for(i=3;i>=0;i--){
			if(ans[i]!=0){
				*size_ans = i+1;
			break;
			}
		}

		printf(" ------- Result (%d): ",*size_ans);
		for(i=3;i>=0;i--){
			printf(" %d",ans[i]);
		}
		printf("\n");
	}

	if (size_inp == 4){
		printf("================= \n");
		printf("sizeProdLow = %d\n", size_prodLow);
		printf("sizeprodMid = %d\n", size_prodMid);
		printf("sizeProdHigh = %d\n", size_prodHigh);
		ans[0]=prodLow[0];
		ans[1]=prodMid[0]+prodLow[1];
		carry=ans[1]/100000000;
		ans[1]=ans[1]%100000000;

		ans[2]=prodHigh[0]+prodMid[1]+prodLow[2]+carry;
		carry=ans[2]/100000000;
		ans[2]=ans[2]%100000000;

		ans[3]=prodHigh[1]+prodMid[2]+prodLow[3]+carry;
		carry=ans[3]/100000000;
		ans[3]=ans[3]%100000000;

		ans[4]=prodHigh[2]+prodMid[3]+carry;
		carry=ans[4]/100000000;
		ans[4]=ans[4]%100000000;

		ans[5]=prodHigh[3]+carry;
		carry=ans[5]/100000000;
		ans[5]=ans[5]%100000000;

		for(i=5;i>=0;i--){
			if(ans[i]!=0){
				*size_ans = i+1;
			break;
			}
		}
		printf(" ------- Result (%d): ",*size_ans);
		for(i=5;i>=0;i--){
			printf(" %d",ans[i]);
		}
		printf("\n");
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	long long a1[4],a2[4],r[8];
	int i=0, size_ans;

	for(i=0;i<7;i++)
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
	a2[2]=24709369;
	a2[3]=62497757;
	/*a2[4]=0;
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
	a1[2]=16939937;
	a1[3]=2884197;
	/*a1[4]=0;
	a1[5]=0;
	a1[6]=0;
	a1[7]=0;*/

	prod(a1,a2,4,r,&size_ans);

	printf("Final= ");
	for(i=size_ans-1;i>=0;i--)
		printf("%lld\n", r[i]);
	printf("\n");
	return 0;
}