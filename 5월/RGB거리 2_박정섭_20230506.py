n=int(input())

costs=[]
for _ in range(n):
    costs.append(list(map(int,input().split())))

INF=float('inf')

def solution(n,costs):
    ans=INF

    for i in range(3):
        dp=[[INF for _ in range(3)] for _ in range(n)]
        dp[0][i]=costs[0][i]
        for k in range(1,n):
            for j in range(3):
                dp[k][j]=min(dp[k-1][(j+1)%3],dp[k-1][(j+2)%3])+costs[k][j]
        ans=min([ans,dp[n-1][(i+1)%3],dp[n-1][(i+2)%3]])
    return ans

print(solution(n,costs))