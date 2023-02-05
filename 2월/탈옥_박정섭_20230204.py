import sys
from collections import deque

n=int(input())
dx=[-1,1,0,0]
dy=[0,0,-1,1]

def bfs(x,y):
    visited=[[-1]*(c+2) for _ in range(r+2)]
    visited[x][y]=0
    q=deque()
    q.append([x,y])
    while q:
        cx,cy=q.popleft()
        for i in range(4):
            nx=cx+dx[i]
            ny=cy+dy[i]
            if 0<=nx<r+2 and 0<=ny<c+2:
                if visited[nx][ny]==-1:
                    if board[nx][ny]=='.' or board[nx][ny]=='$':
                        visited[nx][ny]=visited[cx][cy]
                        q.appendleft([nx,ny])
                    elif board[nx][ny]=='#':
                        visited[nx][ny]=visited[cx][cy]+1
                        q.append([nx,ny])
    return visited

for _ in range(n):
    r,c=map(int,input().split())

    board=[list('.'*(c+2))]
    for i in range(r):
        board.append(list('.'+input().strip()+'.'))
    board.append(list('.'*(c+2)))
    
    prisoner=[]

    for i in range(r+2):
        for j in range(c+2):
            if board[i][j]=='$':
                prisoner.append([i,j])

    p1=bfs(prisoner[0][0],prisoner[0][1])
    p2=bfs(prisoner[1][0],prisoner[1][1])
    sanggeun=bfs(0,0)
    answer=sys.maxsize

    for i in range(r+2):
        for j in range(c+2):
            if p1[i][j]==-1 or p2[i][j]==-1 or sanggeun[i][j]==-1:
                continue    #왜 이걸 넣었을 때 통과하는거지?
            temp=p1[i][j]+p2[i][j]+sanggeun[i][j]
            if board[i][j]=='*':
                continue
            elif board[i][j]=='#':
                temp-=2
            answer=min(answer,temp)
    print(answer)