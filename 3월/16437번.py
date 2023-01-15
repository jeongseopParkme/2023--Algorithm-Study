from collections import deque

n=int(input())
island=[0,0]
parent_node=[0,0]
tree=[[] for _ in range(n+1)]

for i in range(2,n+1):
    t,a,p=input().split()
    a,p=map(int,[a,p])
    if t=='W':
        island.append(-a)
    else:
        island.append(a)
    parent_node.append(p)
    tree[p].append(i)

queue=deque()
queue.append(1)
stack=[]

while queue:
    cur=queue.popleft()
    stack.append(cur)
    for node in tree[cur]:
        queue.append(node)

for cur_node in stack[::-1]:
    island[parent_node[cur_node]]+=max(0,island[cur_node])

print(island[1])
