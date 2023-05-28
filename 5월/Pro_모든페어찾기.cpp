/*
*   1. [lo, hi]�� Check(lo) != Check(hi)�� �ǵ��� ������ ����
*
*   2. while (lo + 1 < hi)���� mid = (lo + hi) / 2���� Check(mid) = Check(lo)��� lo = mid, �ƴ϶�� hi = mid
*
*   3. ���� ��迡�� ���� lo���� hi���� �����غ��� ���
*
*   (1���� ���� �׻� [lo, hi] ���� �����ϰ�, 
*   2���� Check(lo), Check(hi)�� ������ ������, 3���� lo + 1 >= hi�̰�, lo < mid < hi���� lo < hi�̹Ƿ� lo + 1 == hi�� �����մϴ�)
*/
#include <cstring>
#define MAX_DIFF 50000
extern bool checkCards(int mIndexA, int mIndexB, int mDiff);

int binarySearch(int a, int b, int N)
{
    int low = -1, high = N; //-1�� �׻� false, N�� �׻� true
    while (low + 1 < high)
    {
        int mid = (low + high) / 2;
        if (checkCards(a, b, mid) == checkCards(a, b, low))
            low = mid;
        else
            high = mid;
    }
    return high;
}

void check(int diff, int diffArr[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
            checkCards(diffArr[diff][i], diffArr[diff][j], 0);
    }
}

void playGame(int N)
{
    // �� ī���� ���ڸ� ���ϱ� ���� �Ʒ��� ���� checkCards �Լ��� ����մϴ�.
    // <����>
    //
    // checkCards(mIndexA, mIndexB, mDiff);
    int pivot = 0, highIdx = 2 * N - 1;
    int diffArr[MAX_DIFF][4], diffPointer[MAX_DIFF];
    memset(diffArr, 0, sizeof(diffArr));
    memset(diffPointer, 0, sizeof(diffPointer));

    diffArr[0][diffPointer[0]++] = pivot;

    for (int i = 1; i <= highIdx; i++)
    {
        int diff = binarySearch(pivot, i, N);
        diffArr[diff][diffPointer[diff]++] = i;
    }

    for (int i = 0; i < N; i++)
        check(i, diffArr);
}