#include<stdio.h>
#include<limits.h>
int minrod(int arr[],int n,int l){
	if(l==0)
		return 0;
		if(l<0)
			return INT_MAX;		
	int minrods=INT_MAX;
	for(int i=0;i<n;i++){
		int res=minrod(arr,n,l-arr[i]);
		if(res!=INT_MAX){
		if(res+1<minrods){
			minrods=res+1;
		}
	}
	return minrods;
}
}
int minrods(int arr[],int n,int l){
	int result=minrod(arr,n,l);
	if(result==INT_MAX){
		return -1;
	}else{
		return result;
	}
}
int main(){
	int n,l;
	int arr[100];
	printf("enter the number of rods:");
	scanf("%d",&n);
	printf("enter the length(L):");
	scanf("%d",&l);
	if(n>100){
		printf("max no. of rods allow is 100.\n");
		return -1;
	}
	printf("enter the length:");
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	int result=minrods(arr,n,l);
	if(result==-1){
		printf("it is not to achieve the target %d\n",l);
	}else{
		printf("the min numberof rods required to achieve length %d is %d\n",l,result);
	}
	return 0;
}