check=set()
a,b,c=map(int,input().split())

stack=[]
lis=[a,b,c]
lis.sort()
stack.append(lis)
check.add(str(lis[0])+str(lis[1])+str(lis[2]))

while stack:
    x,y,z=stack.pop()
    
    if y!=z:
        tmp=[x,y+y,z-y]
        tmp.sort()
        s=str(tmp[0])+str(tmp[1])+str(tmp[2])
        if s not in check:
            check.add(s)
            stack.append(tmp)
    if x!=z:
        tmp=[x+x,y,z-x]
        tmp.sort()
        s=str(tmp[0])+str(tmp[1])+str(tmp[2])
        if s not in check:
            check.add(s)
            stack.append(tmp)
    if x!=y:
        tmp=[x+x,y-x,z]
        tmp.sort()
        s=str(tmp[0])+str(tmp[1])+str(tmp[2])
        if s not in check:
            check.add(s)
            stack.append(tmp)
s=str(sum(lis)//3)+str(sum(lis)//3)+str(sum(lis)//3)
if s in check:
    print(1)
else:
    print(0)