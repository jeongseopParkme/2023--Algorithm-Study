/*
*   segment tree + range update
* 
*   �켱, max - min = top�̰�
*   count = sum - min * C ��� ����� �˾�ä�� �Ѵ�.
* 
*   �׷� ������ 'min,max�� ��� dropBlocks(N, �ִ� 3,000)���� update�� ���ΰ�' �̴�.
*   
*   Query�� �� ���̸� K(�ִ� 1,000,000)��� ���� ��
*   1. K�� �� �����鼭 min,max�� update���� �� => O(K) => O(NK) => 30�� => fail
*   2. segment tree�� update => O(KlogK) => O(NKlogK) => 30�� �̻� => fail
*   
*   ���� K���� ���� logK�� update�� �����ؾ� �Ѵ�. 
*   �̶� ����� �� �ִ� ����� lazy segment tree�̴�.
*   �ٸ�, �� ������ Query�� �׻� root node�� ���ؼ��� ������ ������, propagation������ �ʿ���� lazy segment tree�� ����� �� �ִ�.
* 
*   https://www.notion.so/einsteinandfeynman/58880eb92c5e4ad3bddd7b12c1383c1e?v=9139b381aa744bd090a0854e4a4f9040&p=077d0532f1b247dda8d5222d5dc054f6&pm=s
* 
*   �ǹ���...
*   1. lazy segment tree�� �˾Ҿ�� �ϳ�?
*   2. ���� �����ٸ� �����س¾�� �ϳ�? (�̰� ������ Ǯ���ΰ�?)
* 
*   One More Thing...
*   (A - B) % C == (A%C - B%C + C) % C
*   ex) A = 27, B = 19, C = 10�� ���, +C�� ������ ������ ��
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
