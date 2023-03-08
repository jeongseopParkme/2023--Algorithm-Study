import sys
#import numpy as np
input=sys.stdin.readline

n,m=map(int,input().split())

memory=list(map(int,input().split()))
costs=list(map(int,input().split()))

max_values=[0]*10001
memory_and_costs = list(zip(memory,costs))

for i in range(n):
    tmp=[]
    for j in range(0,10001-memory_and_costs[i][1]):
        if max_values[j+memory_and_costs[i][1]]<max_values[j]+memory_and_costs[i][0]:
            tmp.append((j+memory_and_costs[i][1],max_values[j]+memory_and_costs[i][0]))
    for idx,val in tmp:
        max_values[idx]=val

#print(np.array(max_values))
for i in range(10001):
    if max_values[i]>=m:
        print(i)
        break