/*
* 악마는 디테일에 있다...
* 1. B의 범위가 int를 초과함 => 선언, scanf, parameter에 long long으로 전달해야 했다.
* 2. 입력 matrix가 1000이고, 1번만 거듭제곱할 때 1000이 그대로 나오면 안되고 0이 나와야 한다.
* 
* 풀이는 Divide & Conquer
*/
#include <cstdio>
#include <cstring>
using namespace std;

int N;
long long B;
int matrix[25];
int ans[25];

void mul(int A[], int B[])
{
	int temp[25];
	memset(temp, 0, sizeof(temp));
	/* kij is much faster */
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				temp[i * N + j] = (temp[i * N + j] + A[i * N + k] * B[N * k + j]) % 1000;

	memcpy(ans, temp, sizeof(ans));
}

void divide(long long num)
{
	if (num == 1)
		return;

	if (num % 2)
	{
		divide(num - 1);
		mul(ans, matrix);
	}
	else
	{
		divide(num / 2);
		mul(ans, ans);
	}
}


int main(void)
{
	scanf("%d %lld", &N, &B);
	for (int i = 0; i < N ; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &matrix[i * N + j]);
			ans[i * N + j] = matrix[i * N + j];
		}
	}

	divide(B);

	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", ans[i * N + j] % 1000); //for 2번 comment
		}
		printf("\n");
	}
}