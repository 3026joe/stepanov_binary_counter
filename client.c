#include <stdio.h>
#include<stdlib.h>
#include"assignment_2.h"

int main()
{
	int t;
	scanf("%d",&t);
	for(int j=0;j<t;++j)
	{
		int n;
		//printf("Enter the number of elements:");
		scanf("%d",&n);
		int* numbers=(int*)malloc(sizeof(int)*n);
		for(int i=0;i<n;++i)
			scanf("%d",&numbers[i]);
		printf("%d numbers\n\n",(j+2));
		find_second_greatest(numbers,n);
		printf("\n_______________________________________\n");
	}
}