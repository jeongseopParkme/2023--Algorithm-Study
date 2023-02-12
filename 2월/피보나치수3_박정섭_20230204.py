'''
로컬에서 실행할때는 문제 없는데 백준에서 실해시 에러메세지가 뜬다
'''
dp=dict()
dp[0]=0
dp[1]=1
dp[2]=1
n=int(input())

arr=[]
new=[n]
while new:
    tmp=new.pop()
    arr.append(tmp)
    if tmp%2==0:
        a,b = tmp//2, tmp//2-1
        if a>2:
            new.append(a)
        if b>2:
            new.append(b)
    else:
        a,b = tmp//2+1, tmp//2
        if a>2:
            new.append(a)
        if b>2:
            new.append(b)
arr.sort()

for i in arr:
    if i%2==0:
        dp[i]=(dp[i//2]**2+2*dp[i//2]*dp[i//2-1])%1000000
    else:
        dp[i]=(dp[i//2+1]**2+dp[i//2]**2)%1000000

print(dp[n])

'''
n=int(input())

t = 100000*15
fib=[0]*t
fib[1]=1
fib[2]=1
for i in range(2,t):
    fib[i]=(fib[i-1]+fib[i-2])%1000000

print(fib[n%t])
'''