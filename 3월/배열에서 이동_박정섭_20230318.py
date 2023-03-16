'''
1,1 에서 100,100 까지 bfs하면 n^2
맵상에서 이동할 수 있는 숫자의 범위들을 정하고, 그 범위내에서 1,1에서 n,n까지 이동할 수 있다면
정답은 숫자의 범위의 차다.
그 숫자의 범위는 0~min((1,1)의 값,(n,n)의 값) 에서 max((1,1)의 값,(n,n)의 값)~200이다
'''

import sys
import collections
input=sys.stdin.readline

n=int(input())
dx=[-1,1,0,0]
dy=[0,0,-1,1]

board=[list(map(int,input().split())) for _ in range(n)]
ans=sys.maxsize

for i in range(0,min(board[0][0],board[n-1][n-1])+1):
    for j in range(max(board[0][0],board[n-1][n-1]),201):
        visited=[[False for _ in range(n)] for _ in range(n)]
        q=collections.deque()
        q.append((0,0))
        visited[0][0]=True
        while q:
            x,y = q.popleft()
            for k in range(4):
                nx=x+dx[k]
                ny=y+dy[k]
                if (0<=nx<n) and (0<=ny<n):
                    if not visited[nx][ny] and (i<=board[nx][ny]<=j):
                        q.append((nx,ny))
                        visited[nx][ny]=True
        if visited[n-1][n-1]:
            #print(i,j)
            ans=min(ans,j-i)
            break
print(ans)