/*
* �Ǹ��� �����Ͽ� �ִ�...
* 1. B�� ������ int�� �ʰ��� => ����, scanf, parameter�� long long���� �����ؾ� �ߴ�.
* 2. �Է� matrix�� 1000�̰�, 1���� �ŵ������� �� 1000�� �״�� ������ �ȵǰ� 0�� ���;� �Ѵ�.
* 
* Ǯ�̴� Divide & Conquer
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
			printf("%d ", ans[i * N + j] % 1000); //for 2�� comment
		}
		printf("\n");
	}
}