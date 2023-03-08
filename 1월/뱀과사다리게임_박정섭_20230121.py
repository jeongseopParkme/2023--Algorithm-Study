from collections import deque
import sys

n,m = map(int, input().split())

ladders, snakes = [0 for _ in range(101)], [0 for _ in range(101)]

for _ in range(n):
    a,b=map(int, input().split())
    ladders[a]=b

for _ in range(m):
    a,b=map(int, input().split())
    snakes[a]=b

def solution(ladders,snakes):
    q= deque()
    q.append([0,1])
    INF = sys.maxsize
    board=[INF for _ in range(101)]
    while q:
        #print(q)
        val,x = q.popleft()
        for dx in range(1,7):
            nx=x+dx
            if nx>100:
                continue
            elif board[nx]>val+1:
                if ladders[nx]:
                    q.append([val+1,ladders[nx]])
                    #print(q)
                    board[nx]=val+1
                    board[ladders[nx]]=val+1
                elif snakes[nx]:
                    q.append([val+1,snakes[nx]])
                    board[nx]=val+1
                    board[snakes[nx]]=val+1
                else:
                    q.append([val+1,nx])
                    board[nx] = val+1
    #print(board)
    return board[100]

print(solution(ladders,snakes))