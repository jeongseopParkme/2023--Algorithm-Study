import sys
input=sys.stdin.readline

while True:
    lis=list(map(int,input().split()))
    n=lis.pop(0)
    if n==0:
        break
    
    stack=[]
    ans=0

    for i, h in enumerate(lis):
        while stack and lis[stack[-1]]>lis[i]:
            tmp=stack.pop()
            if not stack:
                width=i
            else:
                width = i - stack[-1] -1
            ans = max(ans,width*lis[tmp])
        stack.append(i)
    
    while stack:
        tmp = stack.pop()
        if not stack:
            width= n
        else:
            width = n - stack[-1] - 1
        ans=max(ans,width*lis[tmp])
    print(ans)