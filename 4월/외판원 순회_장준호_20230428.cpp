// 한 수 배웁니다...

#include <iostream>
#define INF 1e9
using namespace std;

int N;
int cost[16][16];
int dp[16][1 << 16];

int DFS(int now, int visited) {
    if (visited == ((1 << N) - 1)) {
        if (cost[now][0] == 0) return INF;
        return cost[now][0];
    }

    int& ret = dp[now][visited];
    if (ret != 0) return ret;
    ret = INF;

    // 여러 개의 next 중에서 가장 좋은 선택은?
    for (int next = 0; next < N; next++) {
        if (cost[now][next] == 0) continue;
        if (visited & (1 << next)) continue;
        ret = min(ret, cost[now][next] + DFS(next, visited | 1 << next));
    }

    return ret;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> cost[i][j];
        }
    }

    cout << DFS(0, 1);
}

// https://velog.io/@jxlhe46/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EC%99%B8%ED%8C%90%EC%9B%90-%EC%88%9C%ED%9A%8C-%EB%AC%B8%EC%A0%9C
// https://codecollector.tistory.com/1225
// https://velog.io/@dltmdrl1244/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EC%99%B8%ED%8C%90%EC%9B%90-%EC%88%9C%ED%9A%8CTSP-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98