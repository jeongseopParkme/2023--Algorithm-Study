'''
bfs문제
큐에 M의 좌표와 Z의 좌표를 넣은 후 상하좌우를 확인하며 visited를 갱신한다
이때 파이프가 필요한 좌표를 알기 위해 원소들이 전부 다 0의 값을 가지는 board를 만들고
큐에서 뽑은 좌표가 빈칸이면 해당 칸이 파이프가 필요한 자리이니 표시를 한다
'''
import sys

input=sys.stdin.readline

dx=[-1,1,0,0]
dy=[0,0,-1,1]

r,c=map(int,input().split())
board=[]
visited=[[0 for _ in range(c)] for _ in range(r)]

for _ in range(r):
    board.append(list(input().strip()))

dictionary={10:'1',9:'2',5:'3',6:'4',3:'|',12:'-',15:'+'}

for i in range(r):
    for j in range(c):
        if board[i][j]=='1':
            visited[i+1][j]+=1
            visited[i][j+1]+=4
        elif board[i][j]=='2':
            visited[i-1][j]+=2
            visited[i][j+1]+=4
        elif board[i][j]=='3':
            visited[i-1][j]+=2
            visited[i][j-1]+=8
        elif board[i][j]=='4':
            visited[i+1][j]+=1
            visited[i][j-1]+=8
        elif board[i][j]=='|':
            visited[i-1][j]+=2
            visited[i+1][j]+=1
        elif board[i][j]=='-':
            visited[i][j-1]+=8
            visited[i][j+1]+=4
        elif board[i][j]=='+':
            visited[i][j-1]+=8
            visited[i][j+1]+=4
            visited[i-1][j]+=2
            visited[i+1][j]+=1

for i in range(r):
    for j in range(c):
        if board[i][j]=='.' and visited[i][j]!=0:
            print('%d %d %s'%(i+1,j+1,dictionary[visited[i][j]]))
            break
'''

input=sys.stdin.readline

dx=[-1,1,0,0]
dy=[0,0,-1,1]

r,c=map(int,input().split())
board=[]
visited=[[False for _ in range(c)] for _ in range(r)]
erased_block=[[0 for _ in range(c)] for _ in range(r)]

for _ in range(r):
    board.append(list(input().strip()))

q=deque()

for i in range(r):
    for j in range(c):
        if board[i][j] in ('M','Z'):
            #print("#")
            for k in range(4):
                x,y=i+dx[k],j+dy[k]
                #print(x,y)
                if (0<=x<r) and (0<=y<c):
                    if k==2 and board[x][y] in ('1','2','+','-'):
                        if board[x][y]=='1':
                            q.append((x+1,y,1))
                        elif board[x][y]=='+':
                            q.append((x,y-1,2))
                            q.append((x+1,y,1))
                            q.append((x-1,y,0))
                        elif board[x][y]=='2':
                            q.append((x-1,y,0))
                        else:
                            q.append((x,y-1,2))
                        visited[x][y]=True
                    elif k==3 and board[x][y] in ('3','4','+','-'):
                        if board[x][y]=='3':
                            q.append((x-1,y,0))
                        elif board[x][y]=='4':
                            q.append((x+1,y,1))
                        elif board[x][y]=='-':
                            q.append((x,y+1,3))
                        else:
                            q.append((x,y+1,3))
                            q.append((x+1,y,1))
                            q.append((x-1,y,0))
                        visited[x][y]=True
                    elif k==0 and board[x][y] in ('1','4','+','|'):
                        if board[x][y]=='1':
                            q.append((x,y+1,3))
                        elif board[x][y]=='4':
                            q.append((x,y-1,2))
                        elif board[x][y]=='|':
                            q.append((x-1,y,0))
                        else:
                            q.append((x,y+1,3))
                            q.append((x-1,y,0))
                            q.append((x,y-1,2))
                        visited[x][y]=True
                    elif k==1 and board[x][y] in ('2','3','+','|'):
                        if board[x][y]=='2':
                            q.append((x,y+1,3))
                        elif board[x][y]=='3':
                            q.append((x,y-1,2))
                        elif board[x][y]=='|':
                            q.append((x+1,y,1))
                        else:
                            q.append((x,y+1,3))
                            q.append((x+1,y,1))
                            q.append((x,y-1,2))
                        visited[x][y]=True

while q:
    x,y,cost=q.popleft()
    if board[x][y]=='.':
        erased_block[x][y]+=2**cost
        continue
    visited[x][y]=True
    for i in range(4):
        nx,ny=x+dx[i],y+dy[i]
        if (0<=nx<r) and (0<=ny<c):
            if not visited[nx][ny]:
                if board[x][y]=='1':
                    if i==1 or i==3:
                        q.append((nx,ny,i))
                elif board[x][y]=='2':
                    if i==0 or i==3:
                        q.append((nx,ny,i))
                elif board[x][y]=='3':
                    if i==0 or i==2:
                        q.append((nx,ny,i))
                elif board[x][y]=='4':
                    if i==1 or i==2:
                        q.append((nx,ny,i))
                elif board[x][y]=='|':
                    if i==0 or i==1:
                        q.append((nx,ny,i))
                elif board[x][y]=='-':
                    if i==2 or i==3:
                        q.append((nx,ny,i))
                elif board[x][y]=='+':
                    q.append((nx,ny,i))

for i in range(r):
    print(visited[i])
print(np.array(erased_block))

for i in range(r):
    for j in range(c):
        if erased_block[i][j]!=0:
            cx,cy=i,j
            ans=erased_block[i][j]
print('%d %d '%(cx+1,cy+1),end='')
if ans==5:
    print('1')
elif ans==6:
    print('2')
elif ans==10:
    print('3')
elif ans==9:
    print('4')
elif ans==3:
    print('|')
elif ans==12:
    print('-')
elif ans==15:
    print('+')
'''