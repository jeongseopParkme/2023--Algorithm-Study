/*
*   segment tree + range update
* 
*   우선, max - min = top이고
*   count = sum - min * C 라는 사실을 알아채야 한다.
* 
*   그럼 관건은 'min,max를 어떻게 dropBlocks(N, 최대 3,000)마다 update할 것인가' 이다.
*   
*   Query의 블럭 길이를 K(최대 1,000,000)라고 했을 때
*   1. K를 쭉 읽으면서 min,max를 update했을 때 => O(K) => O(NK) => 30억 => fail
*   2. segment tree로 update => O(KlogK) => O(NKlogK) => 30억 이상 => fail
*   
*   따라서 K보다 작은 logK로 update를 진행해야 한다. 
*   이때 사용할 수 있는 방법이 lazy segment tree이다.
*   다만, 이 문제는 Query가 항상 root node에 대해서만 들어오기 때문에, propagation과정이 필요없는 lazy segment tree를 사용할 수 있다.
* 
*   https://www.notion.so/einsteinandfeynman/58880eb92c5e4ad3bddd7b12c1383c1e?v=9139b381aa744bd090a0854e4a4f9040&p=077d0532f1b247dda8d5222d5dc054f6&pm=s
* 
*   의문점...
*   1. lazy segment tree를 알았어야 하나?
*   2. 만약 몰랐다면 생각해냈어야 하나? (이게 유일한 풀이인가?)
* 
*   One More Thing...
*   (A - B) % C == (A%C - B%C + C) % C
*   ex) A = 27, B = 19, C = 10인 경우, +C가 없으면 음수로 감
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <cstring>
#include <algorithm>

#define MAX 4000000
#define ROOT 1
#define DIVIDE 1000000

long long sum;
int C;

struct Result
{
    int top;
    int count;
};

struct node
{
    int min, max, height;
} segtree[MAX];

void init(int C)
{
    memset(segtree, 0, sizeof(segtree));
    sum = 0;
    ::C = C;
}

//nstart, nend = node start, node end
//qstart, qend = query start, query end
void segUpdate(int node, int nstart, int nend, int qstart, int qend, int height)
{
    if (nend < qstart || qend < nstart)
        return;

    if (qstart <= nstart && nend <= qend)
    {
        segtree[node].height += height;
        return;
    }

    if (nstart == nend)
        return;

    int nmid = (nstart + nend) / 2;
    int left = node * 2;
    int right = node * 2 + 1;
    segUpdate(left,  nstart,   nmid, qstart, qend, height);
    segUpdate(right, nmid + 1, nend, qstart, qend, height);

    segtree[node].min = std::min(segtree[left].min + segtree[left].height, segtree[right].min + segtree[right].height);
    segtree[node].max = std::max(segtree[left].max + segtree[left].height, segtree[right].max + segtree[right].height);
}

Result dropBlocks(int mCol, int mHeight, int mLength)
{
    segUpdate(ROOT, 0, C-1, mCol, mCol + mLength - 1, mHeight);

    sum += mHeight * mLength;
    int top = segtree[ROOT].max - segtree[ROOT].min;
    int count = (sum - (segtree[ROOT].min + segtree[ROOT].height) * C) % DIVIDE;

    return { top, count };
}

#define CMD_INIT 100
#define CMD_DROP 200

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ans_top, ans_count;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int C;
            scanf("%d", &C);
            init(C);
            ok = true;
        }
        else if (query == CMD_DROP)
        {
            int mCol, mHeight, mLength;
            scanf("%d %d %d", &mCol, &mHeight, &mLength);
            Result ret = dropBlocks(mCol, mHeight, mLength);
            scanf("%d %d", &ans_top, &ans_count);
            if (ans_top != ret.top || ans_count != ret.count)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
     freopen("sample_input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
