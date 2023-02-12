/*
*	segment tree + divide and conquer
* 
*	1. segment tree�� �̿��Ͽ� �ּҰ��� ���� index��, �ش� �ּҰ��� �غ����� �ϴ� ���簢���� ���̸� ���Ѵ�.
*	2. �ּҰ� index �������� ���ʰ� �������� ����� ������ �ִ� ���̸� ���Ѵ�.
*	3. 1, 2���� ���� ���� �� ���� ū ���� return�Ѵ�.
*	4. 1, 2, 3�� ����Լ��� �ݺ��Ѵ�.
* 
* ==================================================================================================================
* 
*	segment tree �����
* 
*	0. size ����
*		- h = ceil(log2(n))
*		- tree_size = 1<<(h+1)
*		- �������� 4*n
* 
*	1. init
*		- leaf node���� �� �ڽ��� ���� ������ return
*		- ���� �ڽ� ���� ������ �ڽ� ��带 ��������� ȣ���Ͽ� Ư��(i.e max, min, sum...)�� ���� ���� �����ϰ� return
* 
*	2. query(start~end : node�� Ŀ���ϴ� ���� / left~right : ã���� �ϴ� ����)
*		- start�� end�� left�� right�� ��ġ�� ������ -1(NaN)�� return
*		- start�� end�� left�� right�� ���ϸ� node�� ���� return
*		- �׷��� ������ [start~mid], [mid+1~end]�� ������ ��������� ȣ���Ͽ� return
* 
*	3. update
*		- [start, end]�� index�� ������ ������ return
*		- [start, end]�� index�� ���ϸ� node�� ���� Ư���� �°� �����ϰ� return (leaf node�� ��� ����)
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