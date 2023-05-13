n=int(input())
k=int(input())

dp=[[0 for _ in range(n+1)] for _ in range(n+1)]

def combination(n,k):
    if n/k==2:
        return 2
    if k==1:
        return n
    if not dp[n][k]:
        ans = combination(n-1,k) + combination(n-2,k-1)
        dp[n][k]=ans
    return dp[n][k]

if (n/2<k):
    print(0)
else:
    print(combination(n,k)%1000000003)