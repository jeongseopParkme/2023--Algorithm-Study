from collections import deque
#import numpy as np

n,m = map(int, input().split())
dx=[-1,1,0,0]
dy=[0,0,-1,1]

board=[]
for _ in range(m):
    board.append(input())

def bfs(x1,y1,x2,y2):
    visited=[[-1]*n for _ in range(m)]
    visited[x1][y1]=0
    q=deque()
    q.append([-1,x1,y1])

    while q:
        val,x,y=q.popleft()
        for i in range(4):
            nx,ny=x+dx[i],y+dy[i]
            while (0<=nx<m) and (0<=ny<n) and (board[nx][ny]=='.' or board[nx][ny]=='C'):
                if visited[nx][ny]==-1:
                    q.append([val+1,nx,ny])
                    visited[nx][ny]=val+1
                nx,ny=nx+dx[i],ny+dy[i]
    #print(np.array(visited))
    return visited[x2][y2]

c_coordinate=[]

for i in range(m):
    for j in range(n):
        if board[i][j]=='C':
            c_coordinate.append([i,j])

print(bfs(c_coordinate[0][0],c_coordinate[0][1],c_coordinate[1][0],c_coordinate[1][1]))