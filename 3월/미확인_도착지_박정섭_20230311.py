import sys
import heapq as hq
input=sys.stdin.readline

def dijsktra(node):
    heap=[(0,0,s)]

    while heap:
        dis,check,cur = hq.heappop(heap)
        if distances[cur]<=dis:
            continue
        distances[cur]=dis
        check_point[cur]=check
        for nex,nex_dis in graph[cur]:
            cost = dis + nex_dis
            if cost <=distances[nex]:
                if (cur,nex) == (h,g) or (g,h)==(cur,nex):
                    hq.heappush(heap,(cost,-1,nex))
                else:
                    hq.heappush(heap,(cost,check,nex))
    ans=[]

    for candidate in dest_candidates:
        if check_point[candidate]==-1:
            ans.append(candidate)
    
    return ans

T=int(input())
for _ in range(T):
    n,m,t=map(int,input().split())
    s,g,h=map(int,input().split())

    graph=[[] for _ in range(n+1)]

    for _ in range(m):
        a,b,d=map(int,input().split())
        graph[a].append((b,d))
        graph[b].append((a,d))

    dest_candidates=[]
    distances=[sys.maxsize for _ in range(n+1)]
    check_point=[False for _ in range(n+1)]

    for _ in range(t):
        dest_candidates.append(int(input()))

    ans = dijsktra(s)
    ans.sort()
    for a in ans:
        print(a,end=" ")
    print()