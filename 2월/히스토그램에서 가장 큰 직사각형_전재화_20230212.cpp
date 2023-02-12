/*
*	segment tree + divide and conquer
* 
*	1. segment tree를 이용하여 최소값을 가진 index와, 해당 최소값을 밑변으로 하는 직사각형의 넓이를 구한다.
*	2. 최소값 index 기준으로 왼쪽과 오른쪽을 나누어서 각각의 최대 넓이를 구한다.
*	3. 1, 2에서 구한 넓이 중 가장 큰 값을 return한다.
*	4. 1, 2, 3을 재귀함수로 반복한다.
* 
* ==================================================================================================================
* 
*	segment tree 만들기
* 
*	0. size 설정
*		- h = ceil(log2(n))
*		- tree_size = 1<<(h+1)
*		- 귀찮으면 4*n
* 
*	1. init
*		- leaf node에는 내 자신의 값을 저장후 return
*		- 왼쪽 자식 노드와 오른쪽 자식 노드를 재귀적으로 호출하여 특성(i.e max, min, sum...)을 가진 값을 저장하고 return
* 
*	2. query(start~end : node가 커버하는 범위 / left~right : 찾고자 하는 범위)
*		- start와 end가 left와 right와 겹치지 않으면 -1(NaN)을 return
*		- start와 end가 left와 right에 속하면 node의 값을 return
*		- 그렇지 않으면 [start~mid], [mid+1~end]로 나누어 재귀적으로 호출하여 return
* 
*	3. update
*		- [start, end]에 index가 속하지 않으면 return
*		- [start, end]에 index가 속하면 node의 값을 특성에 맞게 변경하고 return (leaf node면 재귀 종료)
*/
#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;

ll histo[100000];
int n;

int init(int* tree, int node, int start, int end)
{
	if (start == end)
		return tree[node] = start;

	int mid = (start + end) / 2;
	int left = init(tree, node * 2, start, mid);
	int right = init(tree, node * 2 + 1, mid + 1, end);

	return tree[node] = histo[left] <= histo[right] ? left : right;
}

int query(int* tree, int node, int start, int end, int left, int right)
{
	if (right < start || end < left)
		return -1;

	if (left <= start && end <= right)
		return tree[node];

	int mid = (start + end) / 2;
	int left_index = query(tree, node * 2, start, mid, left, right);
	int right_index = query(tree, node * 2 + 1, mid + 1, end, left, right);

	if (left_index == -1)
		return right_index;
	else if (right_index == -1)
		return left_index;
	else
		return histo[left_index] <= histo[right_index] ? left_index : right_index;
}

ll worker(int* tree, int left, int right)
{
	int index = query(tree, 1, 0, n - 1, left, right);
	ll area = (right - left + 1) * histo[index];

	if (left <= index - 1)
	{
		ll temp = worker(tree, left, index - 1);
		if (area < temp)
			area = temp;
	}

	if (index + 1 <= right)
	{
		ll temp = worker(tree, index + 1, right);
		if (area < temp)
			area = temp;
	}

	return area;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (true)
	{
		cin >> n;
		if(n == 0)
			break;

		for (int i = 0; i < n; i++)
			cin >> histo[i];
		
		int h = (int)ceil(log2(n));
		int tree_size = (1 << (h + 1));
		int* tree = new int[tree_size];

		init(tree, 1, 0, n - 1);
		cout << worker(tree, 0, n-1) << '\n';
	}
}