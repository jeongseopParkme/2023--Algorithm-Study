import sys
input = sys.stdin.readline

t=int(input())

for _ in range(t):
    k = int(input())
    lis = list(map(int,input().split()))
    dp=[[0]*(k+1) for _ in range(k+1)]

    for i in range(k-1):
        dp[i][i+1] = lis[i]+lis[i+1]
        for j in range(i+2,k):
            dp[i][j] = dp[i][j-1] + lis[j]
    
    for v in range(2,k):
        for i in range(k-v):
            j = i+v
            dp[i][j] +=min([dp[i][h]+dp[h+1][j] for h in range(i,j)])

    print(dp[0][k-1])