#bottom-up 으로 품

import collections

n=int(input())
graph=[]

INF=float('inf')

for i in range(n):
    graph.append(list(map(int,input().split())))

def bfs():
    dp=[[INF for _ in range(n)] for _ in range(2**n)]

    queue=collections.deque()

    queue.append((1,0))
    dp[1][0]=0

    while queue:
        val,cur=queue.popleft()

        for i in range(n):
            if (val & (2**i)) == 0 and graph[cur][i]!=0:
                nxt = val + (2**i)
                if dp[nxt][i]!=INF:
                    dp[nxt][i]=min(dp[nxt][i],dp[val][cur]+graph[cur][i])
                else:
                    dp[nxt][i]=dp[val][cur]+graph[cur][i]
                    queue.append((nxt,i))
    #print(dp)
    #print([dp[2**n-1][i]+graph[i][0] if graph[i][0]!=0 else INF for i in range(n)])
    return min([dp[2**n-1][i]+graph[i][0] if graph[i][0]!=0 else INF for i in range(n)])

print(bfs())