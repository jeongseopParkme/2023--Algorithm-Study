n,m = map(int,input().split())

def solution(n,k):
    ans=1
    for i in range(n-k+1,n+1):
        ans*=i
    for j in range(1,k+1):
        ans/=j
    return int(ans)%1000000007

print(solution(n,m))