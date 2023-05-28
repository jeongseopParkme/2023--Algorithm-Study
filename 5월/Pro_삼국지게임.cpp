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

    //군주 mMonarchA 와 군주 mMonarchB 가 동맹관계 이면 -1을 반환하고, 전투는 일어나지 않는다.
    if (pA == pB)
        return -1;

    //군주 mMonarchA 의 영토 또는 동맹 영토가 군주 mMonarchB 의 영토와 인접하지 않다면 -2을 반환하고, 전투는 일어나지 않는다.
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

    //전투가 발생하면 군주 mMonarchA 의 동맹과 군주 mMonarchB 의 동맹은 서로 적대관계가 된다.
    enemy[pA][pB] = true;
    enemy[pB][pA] = true;

    //전투가 발생하면 군주 mMonarchB 의 영토에 인접한 군주 mMonarchA 를 포함한 모든 동맹들은 보유한 병사의 절반을 보내 함께 공격한다.
    //군주 mMonarchB 의 영토에 인접한 군주 mMonarchB 의 모든 동맹들도 보유한 병사의 절반을 mMonarchB 의 영토로 보내 방어를 돕는다.
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

    //방어하는 쪽의 병사가 남았거나, 모든 병사가 사망한 경우 0을 반환한다.
    if (numB >= numA)
    {
        soldier[idx] = numB - numA;
        return 0;
    }

    //공격하는 쪽의 병사가 남았다면, 공격 성공으로 1을 반환하고,    
    soldier[idx] = numA - numB;

    //mMonarchB 가 다스렸던 영토는 멸망하여 동맹관계도 적대관계도 없는 새로운 영토가 된다.
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

    //새로운 영토의 군주는 mGeneral 이 되고, mMonarchA의 동맹에 편입되며, 적대 관계는 mMonarchA 의 적대 관계와 동일하다.
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