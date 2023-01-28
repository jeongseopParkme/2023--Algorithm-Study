import sys
input = sys.stdin.readline

n,b=map(int, input().split())
mat=[]
for _ in range(n):
    mat.append(list(map(int,input().split())))

def mat_multiply(mat1, mat2):
    n=len(mat1)
    res=[[0]*n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                res[i][j]+=mat1[k][j]*mat2[i][k]
            res[i][j]=res[i][j]%1000
    return res

def solution(n,b,mat):
    if b==1:
        for i in range(n):
            for j in range(n):
                mat[i][j]=mat[i][j]%1000
        return mat
    else:
        tmp = solution(n,b//2,mat)
        if b%2==0:
            return mat_multiply(tmp,tmp)
        else:
            return mat_multiply(mat_multiply(tmp,tmp),mat)

ans=solution(n,b,mat)

for i in range(n):
    for j in range(n):
        print(ans[i][j],end=" ")
    print()