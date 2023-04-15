#문제 안읽어서 뻘짓함
#10으로 나눈거
#visited에다가 1,2,3,4...이렇게 구분하면서 영역 표시하고 각 영역 몇갠지 갯수 세는 방식

n,m = map(int,input().split())

dx=[-1,1,0,0]
dy=[0,0,-1,1]

board = []

cnt=0

for _ in range(n):
    board.append(list(map(int,list(input()))))

def dfs(y,x,visited):
    global cnt
    if board[y][x]==0 and visited[y][x]==0:
        cnt+=1
        stack=[]
        stack.append((x,y))
        visited[y][x]=cnt
    else:
        return
    while stack:
        cx,cy = stack.pop()
        for i in range(4):
            nx,ny=cx+dx[i],cy+dy[i]
            if (0<=ny<n) and (0<=nx<m):
                if visited[ny][nx]==0 and board[ny][nx]==0:
                    stack.append((nx,ny))
                    visited[ny][nx]=cnt
    return


def solution():
    
    visited = [[0 for _ in range(m)] for _ in range(n)]
    count_map = [0] * (n*m+1)

    for y in range(n):
        for x in range(m):
            dfs(y,x,visited)
    
    for y in range(n):
        for x in range(m):
            if visited[y][x]!=0:
                count_map[visited[y][x]]+=1

    ans_map = [[0 for _ in range(m)] for _ in range(n)]

    for y in range(n):
        for x in range(m):
            if board[y][x]==0:
                continue
            tmp=[]
            for i in range(4):
                ny , nx = y+dy[i], x+dx[i]
                if(0<=ny<n) and (0<=nx<m):
                    tmp.append(visited[ny][nx])
            tmp=list(set(tmp))
            temp=1
            for num in tmp:
                temp+=count_map[num]
            ans_map[y][x]=temp%10

    for lis in ans_map:
        print("".join(map(str,lis)))

    return

solution()