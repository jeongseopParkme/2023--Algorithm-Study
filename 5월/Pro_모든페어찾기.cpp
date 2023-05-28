/*
*   1. [lo, hi]가 Check(lo) != Check(hi)가 되도록 구간을 설정
*
*   2. while (lo + 1 < hi)동안 mid = (lo + hi) / 2에서 Check(mid) = Check(lo)라면 lo = mid, 아니라면 hi = mid
*
*   3. 구한 경계에서 답이 lo인지 hi인지 생각해보고 출력
*
*   (1에서 경계는 항상 [lo, hi] 내에 존재하고, 
*   2에서 Check(lo), Check(hi)는 변하지 않으며, 3에서 lo + 1 >= hi이고, lo < mid < hi에서 lo < hi이므로 lo + 1 == hi를 만족합니다)
*/
#include <cstring>
#define MAX_DIFF 50000
extern bool checkCards(int mIndexA, int mIndexB, int mDiff);

int binarySearch(int a, int b, int N)
{
    int low = -1, high = N; //-1은 항상 false, N은 항상 true
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
    // 두 카드의 숫자를 비교하기 위해 아래와 같이 checkCards 함수를 사용합니다.
    // <영문>
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