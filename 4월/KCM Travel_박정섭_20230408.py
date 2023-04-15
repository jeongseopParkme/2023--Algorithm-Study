'''
dp
밑에 알고리즘은 봄

첫번째 오착 : 두 도시를 잇는 경로는 유일하다 생각. 하지만 비용과 시간이 다른 경로가 있을 수 있다.
-> 답지 봄
'''
import sys
import heapq as hq

input=sys.stdin.readline

INF=float('inf')
t = int(input())

for _ in range(t):
    n,m,k = map(int,input().split())
    dp=[[INF for _ in range(m+1)] for _ in range(n+1)]
    edges=[[] for _ in range(n+1)]

    for _ in range(k):
        u,v,c,d = map(int,input().split())
        edges[u].append((v,c,d))

    heap=[]
    hq.heappush(heap,(0,0,1))
    
    while heap:
        cur_time,cur_cost,cur_node = hq.heappop(heap)
        if cur_time > dp[cur_node][cur_cost]:
            continue
        else:
            for c in range(cur_cost,m+1):
                if dp[cur_node][c] > cur_time:
                    dp[cur_node][c]=cur_time
                else:
                    break
        for v,c,d in edges[cur_node]:
            if cur_cost+c <= m:
                hq.heappush(heap,(cur_time+d,cur_cost+c,v))

    if dp[n][m]==INF:
        print("Poor KCM")
    else:
        print(dp[n][m])
