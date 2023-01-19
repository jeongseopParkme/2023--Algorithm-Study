#include <iostream>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, less<int>>		maxHeap;
priority_queue<int, vector<int>, greater<int>>	minHeap;
int N;
int input;
int goToLess, goToGreater;

int main(void) 
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		/* get input */
		cin >> input;

		/* empty case */
		if (maxHeap.size() == 0)
			maxHeap.push(input);
		else
		{
			/* build Queue -> The size of greaterQ is the same as the size of lessQ, or 1 large */
			if (maxHeap.size() == minHeap.size())
				maxHeap.push(input);
			else
				minHeap.push(input);

			/* rebuild Queue -> greaterQ must retain bottom half and lessQ must retain top half */
			if ((goToLess = maxHeap.top()) > (goToGreater = minHeap.top()))
			{
				maxHeap.pop();
				maxHeap.push(goToGreater);
				minHeap.pop();
				minHeap.push(goToLess);
			}
		}

		/* print answer */
		cout << maxHeap.top() << '\n';
	}
}