#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"assignment_2.h"

typedef struct element
{
	int number;
	struct element* next;
}element;

typedef struct bin
{
	element** bin_count;
	int* len;
	int n;
}bin;

static bin* create_bin(int n);
static element** init(int n);														//creates the binary counter structure which is an array of ceil(log2(n)+1) pointers
static element* create_element(int num);											//creates an element for every number as it arrives.
static void insert(bin* b, int num);												//to insert the new number into the binary counter and call merge to perform the appropriate merges and moves
static void merge(bin* b);															//performs all the necessary moves and merges. gives the final state of the binary counter in case length is a perfect power of 2
static void final_merge(bin* b);													//performs the final few moves and merges when length is not a power of 2
static void display(int col, bin* b);												//displays a particular column of the binary counter
static int second_largest(bin* b);													//checks the last column of the binary counter to find the second largest number

void find_second_greatest(int *numbers, int length)
{
	int n=ceil(log2(length))+1;														
	bin* b=create_bin(n);
	for(int i=0;i<length;i++)
	{
		insert(b,numbers[i]);														//inserting each element that is given one at a time into the binary counter
	}						
	final_merge(b);
	printf("\n");
	int s=second_largest(b);														//finding the second largest number
	printf("%d\n",s);
}

static int second_largest(bin* b)
{
	element* h=b->bin_count[b->n-1]->next;											//ignoring the first element as it is the largest in the array
	int max=h->number;																//storing the first element as the default initial maximum
	h=h->next;																		//shifting the pointer
	while(h!=NULL)																	//iterating through the linked lisk
	{
		if(max<h->number)															//if the current maximum is less than the current element
			max=h->number;															//updating the maximum value
		h=h->next;																	//shifting the pointer
	}
	return max;																		//returning the second largest element
}

static bin* create_bin(int n)
{
	bin* b=(bin*)malloc(sizeof(bin));												//creating the binary counter
	b->bin_count=init(n);															//creating an integer array to store the current lengths of each column of the binary counter
	b->n=n;
	b->len=(int*)malloc(sizeof(int)*n);												//calculating the number of columns required
	return b;
}

static element** init(int n)
{
	element** bin_count=(element**)malloc(sizeof(element*)*n);						//creating the array of pointers
	for(int i=0;i<n;++i)
		bin_count[i]=NULL;															//initializing each pointer to NULL
	return bin_count;																//returning a pointer to the array
}

static element* create_element(int num)
{
	element* temp=(element*)malloc(sizeof(element));								//creating a node to store the new number
	temp->number=num;																//storing the number
	temp-> next=NULL;																//initializing the next pointer to NULL
}

static void insert(bin* b, int num)
{
	element* temp=create_element(num);												//creating the new node
	if(b->bin_count[0]==NULL)														//if the 1st column is empty, store the new number there
	{
		b->bin_count[0]=temp;
		b->len[0]=1;																//changing the length of the 1st column
	}
	else
	{
		printf("%d x %d = ",b->bin_count[0]->number, temp->number);					//displaying the match
		if(b->bin_count[0]->number >= temp->number)									//if the 1st column is not empty, a match has to be played between the element present and the new element
			b->bin_count[0]->next=temp;												//adding the new node to the end as it is smaller
		else
		{
			temp->next=b->bin_count[0];												//putting temp above the already present node
			b->bin_count[0]=temp;
		}
		printf("%d %d\n",b->bin_count[0]->number, b->bin_count[0]->next->number);	//displaying the result of the match
		b->len[0]=2;																//changing the length of the column
		merge(b);																	//calling merge to move or merge the first column with the second
	}
}

static void merge(bin* b)
{
	int i=0;
	while(i<b->n-1)																	//iterating through all the columns of the binary counter
	{
		if(b->bin_count[i]!=NULL && b->len[i]==i+2)									//if a column is non empty and its length exceeds the limit, it must be moved or merged with the next column
		{
			if(b->bin_count[i+1]==NULL)		                                 		//if the next column is free, move the current column in
			{
				b->bin_count[i+1]=b->bin_count[i];
				b->len[i+1]=i+2;
				b->bin_count[i]=NULL;
				b->len[i]=0;
			}
			else																	//if the next column is already full then merge with the next column
			{
				display(i+1,b);														//displaying the match to be played between rows that are to be merged
				printf("x ");
				display(i,b);
				printf("= ");
				element* h0=b->bin_count[i];
				element* h1=b->bin_count[i+1];
				if(h0->number >= h1->number)										//if the current columns's top element is larger
				{
					h1->next=h0->next;
					h0->next=h1;
					b->bin_count[i+1]=h0;
				}
				else																//if the next column's top element is larger
				{
					h0->next=h1->next;
					h1->next=h0;
				}																	//in either case, the winning number is put on top, then the losing number, then the rest of the winning set in that order
				b->bin_count[i]=NULL;												//current column pointer is changed to NULL
				b->len[i+1]=i+3;													//lengths of the columns are changed appropriately
				b->len[i]=0;
				display(i+1,b);														//displaying the results of the match
				printf("\n");
			}
		}
		++i;
	}
}

static void final_merge(bin* b)
{
	int i=0;
	while(i<b->n && b->bin_count[i]==NULL)											//iterating through the binary counter until a non empty column is found
		++i;
	int j=i+1;
	while(j<b->n && b->bin_count[j]==NULL)											//finding the next closest non empty column to merge with
		++j;
	if(i<b->n && j<b->n)															//if both columns exist
	{
		display(j,b);																//displaying the match
		printf("x ");
		display(i,b);
		printf("= ");
		element* h0=b->bin_count[i];
		element* h1=b->bin_count[j];
		if(h0->number >= h1->number)												//if the current column wins
		{
			h1->next=h0->next;
			h0->next=h1;
			b->bin_count[j]=h0;
			b->bin_count[i]=NULL;
		}
		else																		//if the next column wins
		{
			h0->next=h1->next;
			h1->next=h0;
			b->bin_count[j]=h1;
			b->bin_count[i]=NULL;
		}
		display(j,b);																//displaying the results of the match
		printf("\n");
		final_merge(b);																//calling final merge until only one column is present
	}
	else if(i<b->n-1 && j==b->n)													//if only one column is non empty
	{
		b->bin_count[b->n-1]=b->bin_count[i];										//moving the non empty column to the last column
		b->bin_count[i]=NULL;														//changing the current pointer to NULL
	}
}

static void display(int col, bin* b)
{
	element* h=b->bin_count[col];
	while(h!=NULL)																	//iterating through the column
	{
		printf("%d ",h->number);													//printing every element
		h=h->next;																	//moving to the next node
	}
}