'''
dp는 만능해법이다
1부터 2000까지 2차원 배열 만들고
1은 1~1
2는 1~3
3은 1~5...
이렇게 펠린드롬인지 기록
'''
import sys
input=sys.stdin.readline

n=int(input())

arr=list(map(int,input().strip().split(" ")))

m=int(input())

dp=[[0 for _ in range(2001)] for _ in range(2001)]

for i in range(1,n+1):
    if i>(n/2):
        tmp=n+1-i
    else:
        tmp=i
    for j in range(tmp):
        if arr[i+j-1]==arr[i-j-1]:
            dp[i-j][i+j]=1
        else:
            break

for i in range(1,n):
    if i>((n-1)/2):
        tmp=n-i
    else:
        tmp=i
    for j in range(tmp):
        if arr[i+j]==arr[i-j-1]:
            dp[i-j][i+j+1]=1
        else:
            break

for _ in range(m):
    a,b=map(int,input().split(" "))
    print(dp[a][b])