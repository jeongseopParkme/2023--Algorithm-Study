from collections import deque
import sys

input = sys.stdin.readline
dx=[-1,1,0,0]
dy=[0,0,-1,1]

def move_swan():
    while q1:
        x,y = q1.popleft()
        if (x,y)==(swan[1][0],swan[1][1]):  #만약 백조2의 좌표를 백조1이 방문했었으면, 그때의 시간을 반환한다
            return True
        for i in range(4):  #이동할 수 공간이 있는지 확인한다
            cx,cy=x+dx[i],y+dy[i]
            if (0<=cx<r and 0<=cy<c):
                if swan_visited[cx][cy]==False:
                    if board[cx][cy]=='.':   #상하 좌우로 확인했는데 만약 얼음이 없고 방문하지 않은 곳이면 q1에 삽입하고 해당 좌표를 방문했다고 한다
                        q1.append([cx,cy])
                    elif board[cx][cy]=='X': #방문하지 않은 곳인데 얼음인 곳은 하루가 지나면 방문할 좌표이다. 그러니 다음 좌표를 보관하는 q2에 삽입한다.
                        q2.append([cx,cy])
                    swan_visited[cx][cy]=True
    return False

def melt_lake():
    while q3:
        x,y = q3.popleft()
        if board[x][y]=='X':
            board[x][y]='.'
        for i in range(4):
            cx,cy=x+dx[i],y+dy[i]
            if (0<=cx<r and 0<=cy<c):
                if lake_visited[cx][cy]==False:  #상하 좌우로 확인해 얼음인 곳을 q4 넣어준다.
                    if board[cx][cy]=='X':
                        q4.append([cx,cy])
                    else:
                        q3.append([cx,cy])
                    lake_visited[cx][cy]=True
    return

r,c = map(int, input().split())
board = []
q1,q2,q3,q4 = deque(), deque(), deque(), deque()
swan=[]
swan_visited=[[False]*c for _ in range(r)]
lake_visited=[[False]*c for _ in range(r)]

for i in range(r):
    row = list(input().strip())
    board.append(row)
    for j in range(c):
        if board[i][j]=='L':
            swan.append([i,j])  #swan[0]은 백조1의 좌표, swan[1]은 백조2의 좌표이다
            q3.append([i,j])
        elif board[i][j]=='.':
            q3.append([i,j])
            lake_visited[i][j]=True   # visited[][][1]은 해당 시간에 호수에 남은 얼음을 의미한다

time=0
q1.append((swan[0][0],swan[0][1]))
board[swan[0][0]][swan[0][1]], board[swan[1][0]][swan[1][1]] = '.', '.'
swan_visited[swan[0][0]][swan[0][1]]=True #visited[][][0]은 백조1이 해당 시간에 갈 수 있는 좌표들을 의미한다

while True:
    melt_lake()
    if move_swan():
        print(time)
        break
    q1,q3 = q2, q4
    q2,q4= deque(), deque()
    time+=1