import sys
import collections
import itertools
input=sys.stdin.readline


'''
풀이 1
더러운 칸이 최대 10개
그럼 10개의 좌표들을 특정 순서로 순회하는 방식이 이동 횟수의 최솟 값이 된다.

시작 좌표를 고정하고 나머지 더러운 칸은 dirty_room에 저장한다.
3차원 dp를 만들어 dp[0은 시작 좌표, 1부터 n(더러운 칸의 수)는 더러운 칸의 좌표][x][y]로 특정 좌표까지 도달하는데 필요한 이동 횟수를 각각 저장하고
permutation을 사용해 수 많은 이동 순서중에 최소 이동 횟수를 구한다.
'''

dx=[-1,1,0,0]
dy=[0,0,-1,1]

while True:
    m,n = map(int,input().split())
    
    check_point=True

    if n==0 and m==0:
        break
    
    board = []
    
    for _ in range(n):
        board.append(list(input().strip()))
    
    dirty_room=[]

    for i in range(n):
        for j in range(m):
            if board[i][j]=="*":
                dirty_room.append((i,j))
            elif board[i][j]=="o":
                x,y = i,j
    dirty_room.insert(0,(x,y))

    dp = [[0]*len(dirty_room) for _ in range(len(dirty_room))]

    for i in range(len(dirty_room)):
        cx,cy = dirty_room[i]
        q = collections.deque()
        q.append((cx,cy,0))
        tmp_board=[[9999]*m for _ in range(n)]
        tmp_board[cx][cy]=0
        #print(tmp_board)
        while q:
            cx,cy,val = q.popleft()
            for j in range(4):
                nx=cx+dx[j]
                ny=cy+dy[j]
                if(0<=nx<n) and (0<=ny<m):
                    if (tmp_board[nx][ny]>val+1) and (board[nx][ny]!="x"):
                        tmp_board[nx][ny]=val+1
                        q.append((nx,ny,val+1))
            #print(q)
        for j in range(len(dirty_room)):
            if tmp_board[dirty_room[j][0]][dirty_room[j][1]]==9999:
                check_point=False
                break
            dp[i][j]=tmp_board[dirty_room[j][0]][dirty_room[j][1]]
    
    if not check_point:
        print(-1)
        continue

    ans=sys.maxsize

    for p in itertools.permutations([i for i in range(1,len(dirty_room))]):
        tmp_list=list(p)
        tmp_list.insert(0,0)
        tmp=0
        for idx,next_idx in zip(tmp_list[:len(tmp_list)],tmp_list[1:]):
            tmp+=dp[idx][next_idx]
            #print(tmp)
        ans=min(ans,tmp)

    print(ans)