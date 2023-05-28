#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int N, len, soldier[625], p[625];
bool enemy[625][625];
unordered_map<string, int> nameTag;
int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };

inline bool isrange(int y, int x) { return y >= 0 && y < N && x >= 0 && x < N; }

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
    ::N = N;
    len = N * N;
    int idx;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            idx = i * N + j;
            soldier[idx] = mSoldier[i][j];
            p[idx] = idx;
            nameTag.insert(make_pair(mMonarch[i][j], idx));
            
        }
    }
}

void destroy()
{
    nameTag.clear();
    memset(enemy, 0, sizeof(enemy));
}


int find_set(int x)
{
    if (x != p[x])
        p[x] = find_set(p[x]);
    return p[x];
}

void Union(int px, int py)
{
    p[py] = px;
    for (int i = 0; i < len; i++)
    {
        if (enemy[py][i])
        {
            enemy[px][i] = true;
            enemy[i][px] = true;
        }
    }
}

int ally(char mMonarchA[11], char mMonarchB[11])
{
    int pA = find_set(nameTag[mMonarchA]);
    int pB = find_set(nameTag[mMonarchB]);

    if (pA == pB)
        return -1;
    else if (enemy[pA][pB])
        return -2;
    else
        Union(pA, pB);
    return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
    int idx;
    int pA = find_set(nameTag[mMonarchA]);
    int pB = find_set((idx = nameTag[mMonarchB]));

    //���� mMonarchA �� ���� mMonarchB �� ���Ͱ��� �̸� -1�� ��ȯ�ϰ�, ������ �Ͼ�� �ʴ´�.
    if (pA == pB)
        return -1;

    //���� mMonarchA �� ���� �Ǵ� ���� ���䰡 ���� mMonarchB �� ����� �������� �ʴٸ� -2�� ��ȯ�ϰ�, ������ �Ͼ�� �ʴ´�.
    int y = idx / N, x = idx % N;
    int ny, nx;
    int numA = 0, numB = soldier[idx];
    bool peace = true;
    for (int dir = 0; dir < 8; dir++)
    {
        ny = y + dy[dir];
        nx = x + dx[dir];
        if (isrange(ny, nx))
        {
            if (pA == find_set(ny * N + nx))
            {
                peace = false;
                break;
            }
        }
    }
    if (peace)
        return -2;

    //������ �߻��ϸ� ���� mMonarchA �� ���Ͱ� ���� mMonarchB �� ������ ���� ������谡 �ȴ�.
    enemy[pA][pB] = true;
    enemy[pB][pA] = true;

    //������ �߻��ϸ� ���� mMonarchB �� ���信 ������ ���� mMonarchA �� ������ ��� ���͵��� ������ ������ ������ ���� �Բ� �����Ѵ�.
    //���� mMonarchB �� ���信 ������ ���� mMonarchB �� ��� ���͵鵵 ������ ������ ������ mMonarchB �� ����� ���� �� ���´�.
    for (int dir = 0; dir < 8; dir++)
    {
        ny = y + dy[dir];
        nx = x + dx[dir];
        if (isrange(ny, nx))
        {
            int nidx = ny * N + nx;
            if (pA == find_set(nidx))
            {
                numA += (soldier[nidx] / 2);
                soldier[nidx] -= (soldier[nidx] / 2);
            }
            else if (pB == find_set(nidx))
            {
                numB += (soldier[nidx] / 2);
                soldier[nidx] -= (soldier[nidx] / 2);
            }
        }
    }

    //����ϴ� ���� ���簡 ���Ұų�, ��� ���簡 ����� ��� 0�� ��ȯ�Ѵ�.
    if (numB >= numA)
    {
        soldier[idx] = numB - numA;
        return 0;
    }

    //�����ϴ� ���� ���簡 ���Ҵٸ�, ���� �������� 1�� ��ȯ�ϰ�,    
    soldier[idx] = numA - numB;

    //mMonarchB �� �ٽ��ȴ� ����� ����Ͽ� ���Ͱ��赵 ������赵 ���� ���ο� ���䰡 �ȴ�.
    vector<int> temp;
    for (int i = 0; i < len; i++)
    {
        if (i != idx && pB == find_set(i))
            temp.emplace_back(i);
    }

    for (int i = 1; i < temp.size(); i++)
        p[temp[i]] = temp[0];

    if (!temp.empty())
    {
        p[temp[0]] = temp[0];
        for (int i = 0; i < len; i++)
        {
            if (enemy[pB][i])
            {
                enemy[temp[0]][i] = true;
                enemy[i][temp[0]] = true;
            }
        }
    }

    for (int i = 0; i < len; i++)
    {
        enemy[idx][i] = false;
        enemy[i][idx] = false;
    }

    //���ο� ������ ���ִ� mGeneral �� �ǰ�, mMonarchA�� ���Ϳ� ���ԵǸ�, ���� ����� mMonarchA �� ���� ����� �����ϴ�.
    p[idx] = idx;
    Union(pA, idx);
    nameTag.erase(mMonarchB);
    nameTag.insert(make_pair(mGeneral, idx));
    return 1;
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
    int idx = nameTag[mMonarch];
    int p = find_set(idx);
    int y = idx / N, x = idx % N;
    int ret = 0;

    if (mOption == 0)
    {
        soldier[idx] += mNum;
        return soldier[idx];
    }

    for (int i = 0; i < len; i++)
    {
        if (p == find_set(i))
        {
            soldier[i] += mNum;
            ret += soldier[i];
        }
    }
    return ret;
}