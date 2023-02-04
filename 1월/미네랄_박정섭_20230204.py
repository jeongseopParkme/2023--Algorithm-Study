import sys
from collections import deque
import numpy as np

input = sys.stdin.readline
r,c = map(int, input().split())

board=[]

for _ in range(r):
    board.append(list(input().strip()))

n= int(input())
height=list(map(int,input().split()))

dx=[0,0,-1,1]
dy=[-1,1,0,0]

#print(np.array(board))

def bfs(x,y):
    q=deque()
    coordinate_group=[]
    visited=[[False for _ in range(c)] for _ in range(r)]
    q.append((x,y))
    coordinate_group.append((x,y))
    visited[x][y]=True
    while q:
        cx,cy  = q.popleft()
        for i in range(4):
            nx=cx+dx[i]
            ny=cy+dy[i]
            if (0<=nx<r and 0<=ny<c) and visited[nx][ny]==False:
                if board[nx][ny]=='x':
                    q.append((nx,ny))
                    visited[nx][ny]=True
                    coordinate_group.append((nx,ny))
    for x,y in coordinate_group:
        if x==r-1:
            return

    temp=dict()
    coordinate_group.sort(key=lambda x:(-x[0],-x[1]))
    for x,y in coordinate_group:
        if y in temp:
            temp[y]=max(temp[y],x)
        else:
            temp[y]=x

    a=100
    for y,x in temp.items():
        h=0
        nx=x+1
        while True:
            if nx<r and board[nx][y]=='.':
                nx+=1
                h+=1
            else:
                a=min(a,h)
                break
        #print(nx,y)
    #print(a,temp)
    for x,y in coordinate_group:
        board[x][y],board[x+a][y]='.','x'
    return

for i in range(len(height)):
    h=r-height[i]+1
    #print(h)
    if i%2==0:
        a=0
        b=c
        for i in range(a,b):
            if board[h-1][i]=='.':
                continue
            else:
                board[h-1][i]='.'
                for j in range(3):
                    nx=h-1+dx[j]
                    ny=i+dy[j]
                    if (0<=nx<r and 0<=ny<c):
                        if board[nx][ny]=='x':
                            bfs(nx,ny)
                        #print(np.array(board))
                break
    else:
        for i in range(c-1,0,-1):
            if board[h-1][i]=='.':
                continue
            else:
                board[h-1][i]='.'
                for j in range(3):
                    nx=h-1+dx[j]
                    ny=i+dy[j]
                    if (0<=nx<r and 0<=ny<c):
                        if board[nx][ny]=='x':
                            bfs(nx,ny)
                        #print(np.array(board))
                break

for i in range(r):
    for j in range(c):
        print(board[i][j],end='')
    print()