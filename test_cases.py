#the code generates 129 test cases with the first i+1 natural numbers in the ith test case
#the output for the ith test case should be i

n=129
for i in range(2,n):
    l=[]
    for j in range(1,i+1):
        l.append(j)
    print(i,end=' ')
    for j in range(0,i):
        print(l[j],'',end='')
    print()