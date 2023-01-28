import heapq as hq

a,b = map(int, input().split())
graph = []

for _ in range(a):
    graph.append(list(input()))

def solution(a,b, graph):
    
    tmp_graph=[[1500]*b for _ in range(a)]
    dx=[-1,1,0,0]
    dy=[0,0,-1,1]

    for i in range(a):
        for j in range(b):
            if graph[i][j]=='L':
                x1=i
                y1=j
                break

    for i in range(a):
        for j in range(b):
            if graph[i][j]=='L' and (i,j)!=(x1,y1):
                x2=i
                y2=j
                break

    for i in range(a):
        for j in range(b):
            if graph[i][j]=='.' or graph[i][j]=='L':
                tmp_graph[i][j]=0

    heap=[]
    for i in range(a):
        for j in range(b):
            if tmp_graph[i][j]==0:
                hq.heappush(heap,(0,i,j))
    
    while heap:
        d,x,y = hq.heappop(heap)
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if nx<a and nx>=0 and ny<b and ny>=0:
                if tmp_graph[nx][ny]==1500:
                    hq.heappush(heap,(d+1,nx,ny))
                    tmp_graph[nx][ny]=d+1
            else:
                continue
    
    heap=[(0,x1,y1)]
    visited=[[False]*b for _ in range(a)]
    visited[x1][y1]==True

    while heap:
        d,x,y=hq.heappop(heap)
        if x==x2 and y==y2:
            return d
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if nx<a and nx>=0 and ny<b and ny>=0:
                if visited[nx][ny]==False:
                    visited[nx][ny]=True
                    hq.heappush(heap,(max(tmp_graph[nx][ny],d),nx,ny))
    return 0

print(solution(a,b,graph))