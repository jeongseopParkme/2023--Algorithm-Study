#import numpy as np

INF=float('inf')

v,e = map(int,input().split())
graph=[[INF for _ in range(v+1)] for _ in range(v+1)]

for _ in range(e):
    a,b,c = map(int,input().split())
    graph[a][b]=c

for i in range(1,v+1):
    graph[i][i]=0

for k in range(1,v+1):
    for i in range(1,v+1):
        for j in range(1,v+1):
            graph[i][j]=min(graph[i][j],graph[i][k]+graph[k][j])

for i in range(1,v+1):
    graph[i][i]=INF

for i in range(1,v+1):
    for j in range(1,v+1):
        if i!=j:
            graph[i][i]=min(graph[i][i],graph[i][j]+graph[j][i])
#print(np.array(graph))
ans=INF

for i in range(1,v+1):
    ans=min(ans,graph[i][i])
if ans!=INF:
    print(ans)
else:
    print(-1)