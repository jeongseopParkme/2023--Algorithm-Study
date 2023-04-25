from collections import deque

Board = [list(input()) for _ in range(8)]
queue = deque()
dr = [-1, -1, -1, 0, 0, 0, 1, 1, 1]
dc = [-1, 0, 1, -1, 0, 1, -1, 0, 1]

def BFS(r, c):
    queue.append((r, c, 0))

    while(queue):
        r, c, t = queue.popleft()
        for i in range(9):
            nr = r + dr[i]
            nc = c + dc[i] 
            rr = 7-t-nr # relative row

            if 0 <= nr < 8 and 0 <= nc < 8:
                if rr >= 0:
                    if Board[rr][nc] == '#':
                        continue
                    if rr > 0 and Board[rr-1][nc] == '#':
                        continue
                if (nr, nc) == (7, 7):
                    return 1
                queue.append((nr, nc, t+1))

    return 0

print(BFS(0, 0))

## visited!!