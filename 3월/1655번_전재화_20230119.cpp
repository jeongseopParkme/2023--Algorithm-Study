#include <iostream>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, less<int>>		greaterQueue;
priority_queue<int, vector<int>, greater<int>>	lessQueue;
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
		if (greaterQueue.size() == 0)
			greaterQueue.push(input);
		else
		{
			/* build Queue -> The size of greaterQ is the same as the size of lessQ, or 1 large */
			if (greaterQueue.size() == lessQueue.size())
				greaterQueue.push(input);
			else
				lessQueue.push(input);

			/* rebuild Queue -> greaterQ must retain bottom half and lessQ must retain top half */
			if ((goToLess = greaterQueue.top()) > (goToGreater = lessQueue.top()))
			{
				greaterQueue.pop();
				greaterQueue.push(goToGreater);
				lessQueue.pop();
				lessQueue.push(goToLess);
			}
		}

		/* print answer */
		cout << greaterQueue.top() << '\n';
	}
}