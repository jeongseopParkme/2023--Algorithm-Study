'''
간단한 아이디어 2개
1. 숫자의 길이가 n이면, n-1번 이내에 최댓값을 만들 수 있음
2. 주어진 k가 n이상이면 2씩 낮춰서 n으로 만들어준다

이거 수학적으로 증명 가능한데 1번은 n개의 숫자를 움직이는 경우 생각하면 되고
2번은 홀수번 움직여서 같은 숫자를 만들 수 없다 증명하면 됨

'''

n,k = map(str,input().split(" "))
k=int(k)
m=len(n)

while k>m:
    k-=2

ans=-1

def solution(n,k):
    global ans
    if k==0:
        return
    for i in range(m):
        for j in range(i+1,m):
            if not (i==0 and n[j]=='0'):
                if k==1:
                    ans=max(ans,int(n[0:i]+n[j]+n[i+1:j]+n[i]+n[j+1:]))
                solution(n[0:i]+n[j]+n[i+1:j]+n[i]+n[j+1:],k-1)

solution(n,k)
print(ans)