#include <list>
#include <algorithm>
#include <cstring>
using namespace std;

#define NONE -1
pair<int, int> soldierS_N[100001]; //index = [mID], contents = {team, Serial-Number}
list<pair<int, int>> teamNscore[6][6]; //index = [team][score], contents = {mID, S_N}
int S_N = 0;

void init()
{
    memset(soldierS_N, NONE, sizeof(soldierS_N));
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
            teamNscore[i][j].clear();
    }
    S_N = 0;
}

void hire(int mID, int mTeam, int mScore)
{
    soldierS_N[mID] = { mTeam, S_N };
    teamNscore[mTeam][mScore].push_back({ mID, S_N });
    S_N++;
}

void fire(int mID)
{
    soldierS_N[mID] = { NONE, NONE };
    S_N++;
}

void updateSoldier(int mID, int mScore)
{
    int team = soldierS_N[mID].first;
    soldierS_N[mID] = { team, S_N };
    teamNscore[team][mScore].push_back({ mID, S_N });
    S_N++;
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore > 0)
    {
        for (int nowScore = 4; nowScore >= 1; nowScore--)
        {
            int nextScore = min(nowScore + mChangeScore, 5);
            auto& now = teamNscore[mTeam][nowScore];
            auto& next = teamNscore[mTeam][nextScore];
            next.splice(next.end(), now);
        }
    }
    else if (mChangeScore < 0)
    {
        for (int nowScore = 2; nowScore <= 5; nowScore++)
        {
            int nextScore = max(1, nowScore + mChangeScore);
            auto& now = teamNscore[mTeam][nowScore];
            auto& next = teamNscore[mTeam][nextScore];
            next.splice(next.end(), now);
        }
    }
}

int bestSoldier(int mTeam)
{
    bool find = false;
    int bestmID = 0;
    for (int score = 5; score >= 1 && !find; score--)
    {
        for (auto& it : teamNscore[mTeam][score])
        {
            if (soldierS_N[it.first].second == it.second && bestmID < it.first)
            {
                bestmID = it.first;
                find = true;
            }
        }
    }
    return bestmID;
}