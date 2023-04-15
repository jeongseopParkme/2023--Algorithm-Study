#import numpy as np
temp=[]

for _ in range(8):
    temp.append(list(map(str,input())))

board=[temp]

for _ in range(8):
    tmp=[['.','.','.','.','.','.','.','.']]+board[-1][:7]
    board.append(tmp)

#for i in range(9):
    #print(np.array(board[i]))

dx=[0,1,1,1,0,-1,-1,-1,0]
dy=[-1,-1,0,1,1,1,0,-1,0]

check=False

def dfs(x,y,num):
    global check
    if check:
        return
    if x==7 and y==0:
        check=True
        return
    if num>=8:
        n=8
        m=8
    else:
        n=num
        m=num+1
    if num>=8:
        h=3
    else:
        h=9
    for i in range(h):
        nx,ny=x+dx[i],y+dy[i]
        if (0<=nx<8) and (0<=ny<8) and board[n][ny][nx]!='#' and board[m][ny][nx]!='#':
            #print(nx,ny,board[n][ny][nx],board[m][ny][nx],num)
            dfs(nx,ny,num+1)
    return

dfs(0,7,0)

if check:
    print(1)
else:
    print(0)