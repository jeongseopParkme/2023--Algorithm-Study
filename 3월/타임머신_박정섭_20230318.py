import sys

input=sys.stdin.readline
INF=sys.maxsize

n,m=map(int,input().split())

edges=[]
distance=[INF for _ in range(n+1)]
distance[1]=0

for _ in range(m):
    a,b,c=map(int,input().split())
    edges.append((a,b,c))

for a in range(1,n+1):
    for cur_node,next_node,cost in edges:
        if distance[cur_node]!=INF and distance[cur_node]+cost<distance[next_node]:
            distance[next_node]=distance[cur_node]+cost

def solution():
    for a in range(1,n+1):
        for cur_node,next_node,cost in edges:
            if distance[cur_node]!=INF and distance[cur_node]+cost<distance[next_node]:
                return False
    return True

if solution():
    for d in distance[2:]:
        if d==INF:
            print(-1)
        else:
            print(d)
else:
    print(-1)