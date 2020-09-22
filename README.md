# stepanov_binary_counter
Implements Stepanov's Binary Counter to find the 2nd largest number in an array of numbers using [n + log(n) - 2] comparisons

Data Structures Used:
	*) I've used an adjacency list
	*) I have also used an integer array to keep track of the lengths of each list in the adjacency list
	
	*) struct bin
		->bin_count is the array of pointers which forms the adjacency list
		-> len is the integer array with the lengths of each column
		-> n is the number of columns in the adjacency list
	
	*) struct element
		-> element is each node in the adjacency list
		-> number stores the element at that position
		-> next is a pointer to the next element in the list

I have used the math.h header file so -lm must be used while compiling

Key takeaway from the assignment:
	*) This assignment taught me exactly how Stepanov's binary counter works.
	*) It also taught me how useful it is to make code moudular (by use of functions)
	*) Deciding whether to use an array of arrays or an adjacency list was a bit tedious. I initially decided on an array of arrays, but the manual copying of elements made the code a lot slower despite the memory advantage. Using an adjacency list improved the speed by a lot, and the memory used at a time was less than that of the array of arrays. Thus I picked the latter.
