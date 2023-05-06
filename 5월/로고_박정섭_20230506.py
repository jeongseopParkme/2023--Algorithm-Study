import collections

n=int(input())
dx=[-1,1,0,0]
dy=[0,0,-1,1]

board=[[False for _ in range(2001)] for _ in range(2001)]

ans=0

check=[[False for _ in range(2001)] for _ in range(2001)]

for _ in range(n):
    a,b,c,d=map(int,input().split())
    a,b,c,d=a*2+1000,b*2+1000,c*2+1000,d*2+1000

    for i in range(a,c+1):
        board[i][b]=True
        board[i][d]=True
    
    for i in range(b,d+1):
        board[a][i]=True
        board[c][i]=True
    
if board[1000][1000]:
    ans-=1

queue=collections.deque()

for i in range(2001):
    for j in range(2001):
        if board[i][j] and not check[i][j]:
            ans+=1
            queue.append((i,j))
            check[i][j]=True
            while queue:
                x,y=queue.popleft()
                for k in range(4):
                    #이거 i라 써서 한참 헤멤;;
                    nx,ny=x+dx[k],y+dy[k]
                    if (0<=nx<=2000) and (0<=ny<=2000):
                        if board[nx][ny] and not check[nx][ny]:
                            queue.append((nx,ny))
                            check[nx][ny]=True
        else:
            continue

print(ans)