#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
bool visited[501][501][501];

int BFS(int* arr) {
    int now[3], next[3];
    queue<int*> q;
    q.push(arr);

    while(!q.empty()) {
        int* ptr = q.front();

        for (int i = 0; i < 3; i++) {
            now[i] = *ptr;
            ptr++;
        }
        q.pop();

        if (now[0] == now[1] && now[1] == now[2]) return 1;

        sort(now, now+3);

        for (int i = 0; i < sizeof(now) / sizeof(int); i++) {
            cout << now[i] << ' ';
        }

        cout << endl;

        if (now[0] != now[1]) {
            next[0] = now[0] * 2;
            next[1] = now[1] - now[0];
            next[2] = now[2];
            sort(next, next+3);
            if (!visited[next[0]][next[1]][next[2]]){
                visited[next[0]][next[1]][next[2]] = true;
                q.push(next);
            }
        }

        if (now[0] != now[2]) {
            next[0] = now[0] * 2;
            next[1] = now[1];
            next[2] = now[2] - now[0];
            sort(next, next+3);
            if (!visited[next[0]][next[1]][next[2]]){
                visited[next[0]][next[1]][next[2]] = true;
                q.push(next);
            }
        }

        if (now[1] != now[2]) {
            next[0] = now[0];
            next[1] = now[1] * 2;
            next[2] = now[2] - now[1];
            sort(next, next+3);
            if (!visited[next[0]][next[1]][next[2]]){
                visited[next[0]][next[1]][next[2]] = true;
                q.push(next);
            }
        }
    }

    return 0;

}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int arr[3];
    cin >> arr[0] >> arr[1] >> arr[2];
    cout << BFS(arr);
}
