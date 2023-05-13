n=int(input())

lis=list(map(int,input().split()))

dp1=[1]*n
dp2=[-1]*n

for i in range(n):
    for j in range(i+1,n):
        if lis[i]<lis[j] and dp1[i]>=dp1[j]:
            dp1[j]=dp1[i]+1
            dp2[j]=i

print(max(dp1))
arr=[dp1.index(max(dp1))]
#print(dp2)

while True:
    if dp2[arr[-1]] != -1:
        arr.append(dp2[arr[-1]])
    else:
        break

for idx in arr[::-1]:
    print(lis[idx],end=" ")