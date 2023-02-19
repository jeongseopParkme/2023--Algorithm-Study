import sys
#import numpy as np
input = sys.stdin.readline

n= int(input())
arr=[]

for _ in range(n):
    r,c=map(int, input().split())
    arr.append((r,c))

dp=[[sys.maxsize]*n for _ in range(n)]
for i in range(n):
    dp[i][i]=0

for k in range(1,n):
    for i in range(0,n-k):
        if(k>1):
            for j in range(i,i+k):
                dp[i][i+k]=min(dp[i][i+k],dp[i][j]+arr[i][0]*arr[j][1]*arr[i+k][1]+dp[j+1][i+k])
        else:
            dp[i][i+k]=arr[i][0]*arr[i][1]*arr[i+k][1]
        #print(np.array(dp))

print(dp[0][n-1])