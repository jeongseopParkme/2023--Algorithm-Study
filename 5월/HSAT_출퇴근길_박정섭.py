n,m=map(int,input().split())

graph1=[[]for _ in range(n+1)]
graph2=[[]for _ in range(n+1)]

visited1=[False for _ in range(n+1)]
visited2=[False for _ in range(n+1)]
visited3=[False for _ in range(n+1)]
visited4=[False for _ in range(n+1)]

for _ in range(m):
    a,b=map(int,input().split())
    graph1[a].append(b)
    graph2[b].append(a)

s,t=map(int,input().split())

#print(graph1)
#print(graph2)

q1=[t]
q2=[s]
q3=[t]
q4=[s]

visited1[t]=True
#visited1[s]=True
visited2[s]=True
#visited2[t]=True
visited3[t]=True
visited4[s]=True

#print(q1)
while q1:
    cur=q1.pop()
    for nxt in graph2[cur]:
        if nxt==s:
            continue
        elif not visited1[nxt]:
            q1.append(nxt)
            visited1[nxt]=True
    #print(q1)
#print(q2)
while q2:
    cur=q2.pop()
    for nxt in graph1[cur]:
        if nxt==t:
            continue
        elif not visited2[nxt]:
            q2.append(nxt)
            visited2[nxt]=True
    #print(q2)

while q3:
    cur=q3.pop()
    for nxt in graph1[cur]:
        if nxt==s:
            continue
        elif not visited3[nxt]:
            q3.append(nxt)
            visited3[nxt]=True

while q4:
    cur=q4.pop()
    for nxt in graph2[cur]:
        if nxt==t:
            continue
        elif not visited4[nxt]:
            q4.append(nxt)
            visited4[nxt]=True

'''
print(visited1)
print(visited2)
print(visited3)
print(visited4)
'''
cnt=0

for i in range(1,n+1):
    if visited1[i]&visited2[i]&visited3[i]&visited4[i]:
        cnt+=1
print(cnt)
