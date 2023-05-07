#include <iostream>
#include <queue>
#include <algorithm>

// void Print(const Triple& arr);
// void qPrint(const queue<Triple>& q);

using namespace std;
bool visited[501][501][501] = {false};

struct Triple {
    int x, y, z;
    Triple(int x, int y, int z) : x(x), y(y), z(z) {}
};

int BFS(const Triple& arr) {
    int now[3], next[3];
    visited[arr.x][arr.y][arr.z] = true;
    queue<Triple> q;
    q.push(arr);

    while(!q.empty()) {
        // Pull out the first element from the queue!
        Triple now = q.front(); q.pop();

        // Return 1 if all numbers are the same.
        if (now.x == now.y && now.y == now.z) return 1;

        // If first number is not the same with the second one, do the shit!
        if (now.x != now.y) {
            next[0] = now.x * 2;
            next[1] = now.y - now.x;
            next[2] = now.z;
            sort(next, next+3);
            if (!visited[next[0]][next[1]][next[2]]){
                visited[next[0]][next[1]][next[2]] = true;
                q.push(Triple(next[0], next[1], next[2]));
            }
        }

        // If first number is not the same with the third one, do the shit!
        if (now.x != now.z) {
            next[0] = now.x * 2;
            next[1] = now.y;
            next[2] = now.z - now.x;
            sort(next, next+3);
            if (!visited[next[0]][next[1]][next[2]]){
                visited[next[0]][next[1]][next[2]] = true;
                q.push(Triple(next[0], next[1], next[2]));
            }
        }

        // If second number is not the same with the third one, do the shit!
        if (now.y != now.z) {
            next[0] = now.x;
            next[1] = now.y * 2;
            next[2] = now.z - now.y;
            sort(next, next+3);
            if (!visited[next[0]][next[1]][next[2]]){
                visited[next[0]][next[1]][next[2]] = true;
                q.push(Triple(next[0], next[1], next[2]));
            }
        }
    }

    return 0;

}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int arr[3];
    cin >> arr[0] >> arr[1] >> arr[2];
    sort(arr, arr+3);
    cout << BFS(Triple(arr[0], arr[1], arr[2]));
}


///////////////////// For Debug /////////////////////////
// void Print(const Triple& arr){
//     cout << arr.x << ' ';
//     cout << arr.y << ' ';
//     cout << arr.z << endl;
// }

// void qPrint(const queue<Triple>& q) {
//     queue<Triple> qCopy = q;
//     cout << "qSize = " << qCopy.size() << endl;
//     cout << "---s---" << endl;
//     for (int i = 0; !qCopy.empty(); i++) {
//         Print(qCopy.front());
//         qCopy.pop();
//         cout << "qSize = " << qCopy.size() << endl;
//         cout << "qEmpty = " << qCopy.empty() << endl;
//     }
//     cout << "---e---" << endl;
// }
/////////////////////////////////////////////////////////