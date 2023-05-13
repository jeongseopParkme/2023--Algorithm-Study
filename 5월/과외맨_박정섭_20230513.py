'''
총평
문제가 너무 김
매우 읽기 귀찮습니다
다익스트라로 풀면 될거 같습니다
'''
import sys
import heapq as hq

input=sys.stdin.readline

n=int(input())

tmp=[[]]

for _ in range(n**2-n//2):
    tmp.append(list(map(int,input().strip().split())))

graph=[[] for _ in range(n**2-n//2+1)]

for m in range(1,n**2-n//2+1):
    if (m-n)%(2*n-1)==0:
        a,b,c,e,f,g=0,0,0,m-1,m-n,m+(n-1)
    elif (m-2*n+1)%(2*n-1)==0:
        a,b,c,e,f,g=m+n,m-n+1,0,m-1,m-n,m+(n-1)
    elif (m-(n+1))%(2*n-1)==0:
        a,b,c,e,f,g=m+n,m-n+1,m+1,0,m-n,m+(n-1)
    elif (m-2*n)%(2*n-1)==0 or m==1:
        a,b,c,e,f,g=m+n,m-n+1,m+1,0,0,0
    else:
        a,b,c,e,f,g=m+n,m-n+1,m+1,m-1,m-n,m+(n-1)
    
    arr=[a,b,c,e,f,g]
    #print(arr)
    for x in arr:
        if (1<=x<=n**2-n//2):
            #print(m,x,arr.index(x),tmp[m],tmp[x])
            if arr.index(x)<3 and tmp[m][1]==tmp[x][0]:
                graph[m].append(x)
            elif arr.index(x)>=3 and tmp[m][0]==tmp[x][1]:
                graph[m].append(x)
            #print(graph[m])

def dijsktra():
    heap=[]
    hq.heappush(heap,(1,1,[1]))

    visited=[False for _ in range(n**2-n//2+1)]
    visited[1]=True

    ans_node=1
    ans_lis=[1]
    ans_val=1

    while heap:
        val,cur,lis=hq.heappop(heap)
        for nxt in graph[cur]:
            if not visited[nxt]:
                hq.heappush(heap,(val+1,nxt,lis+[nxt]))
                visited[nxt]=True
                if nxt>ans_node:
                    ans_node=nxt
                    ans_lis=lis+[nxt]
                    ans_val=val+1
    
    #print(graph)
    #print(visited)

    print(ans_val)
    for num in ans_lis:
        print(num,end=" ")
    return

dijsktra()