n,k = map(int,input().split())
div=1000000007

def power(n,p):
    if p==0:
        return 1
    if p%2==1:
        return (power(n,p//2)**2*n)%div
    else:
        return (power(n,p//2)**2)%div

def fac(n):
    num = 1
    for i in range(2,n+1):
        num = (num * i)%div
    return num

print((fac(n)*(power(fac(n-k)*fac(k),div-2)))%div)