#include <iostream>
#include <algorithm>
#define MAX 1001
#define RGB 3
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    int ans = 987654321;
    int dp[MAX][RGB];
    int cost[MAX][RGB];

    cin >> N;

    for (int i = 1; i < N+1; i++) cin >> cost[i][0] >> cost[i][1] >> cost[i][2];


    for (int i = 0; i < RGB; i++) {
        for (int j = 0; j < RGB; j++){
            if (i == j) dp[1][j] = cost[1][j];
            else dp[1][j] = MAX;
        }

        for (int j = 2; j < N+1; j++) {
            dp[j][0] = min(dp[j-1][1], dp[j-1][2]) + cost[j][0];
            dp[j][1] = min(dp[j-1][0], dp[j-1][2]) + cost[j][1];
            dp[j][2] = min(dp[j-1][0], dp[j-1][1]) + cost[j][2];
        }

        for (int j = 0; j < RGB; j++) {
            if (i == j) continue;
            ans = min(ans, dp[N][j]);
        }
    }

    cout << ans;

    return 0;
}