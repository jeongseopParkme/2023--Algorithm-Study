n,m = map(int, input().split())

ladders, snakes = [0 for _ in range(101)], [0 for _ in range(101)]

for _ in range(n):
    a,b=map(int, input().split())
    ladders[a]=b

for _ in range(m):
    a,b=map(int, input().split())
    snakes[a]=b

def solution(ladders,snakes):
    dp=[0 for _ in range(101)]
    for x in range(1,101):
        if x!=1 and dp[x]==0:
            continue
        for dx in range(1,7):
            nx=x+dx
            if nx>100:
                continue
            if not dp[nx]:
                dp[nx]=dp[x]+1
            else:
                dp[nx]=min(dp[nx],dp[x]+1)
            if snakes[nx]:
                if not dp[snakes[nx]]:
                    dp[snakes[nx]]=dp[nx]
                else:
                    dp[snakes[nx]]=min(dp[nx],dp[snakes[nx]])
                dp[nx]=0
            if ladders[nx]:
                if not dp[ladders[nx]]:
                    dp[ladders[nx]]=dp[nx]
                else:
                    dp[ladders[nx]]=min(dp[nx],dp[ladders[nx]])
                dp[nx]=0
    print(dp)
    return dp[100]

print(solution(ladders,snakes))