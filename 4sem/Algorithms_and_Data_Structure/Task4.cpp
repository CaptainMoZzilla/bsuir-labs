#pragma optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;

const long SIZE = 1000;
bool visited[SIZE][SIZE];
long dist[SIZE][SIZE];


long endPolong = 0; // Строго <;
queue<pair<long, long>> top_queue;

const long start_point = 0;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    long n, m;
    long x, y;
    cin >> n >> m >> x >> y;
    endPolong = n * m;



    if ((n == m && m == 1) ||
        (x == y && y == 1)) {
            cout << 0;
            return 0;
    }

    x--; y--;


    for (long a = 0; a < n; a++) {
        for (long b = 0; b < m; b++) {
            visited[a][b] = false;
        }
    }

    visited[start_point][start_point] = true;
    dist[start_point][start_point] = 0;
    top_queue.push(make_pair(start_point, start_point));

    while(!top_queue.empty()) {
        pair<long, long> curr = top_queue.front();

        long i_cur = curr.first;
        long j_cur = curr.second;

        top_queue.pop();

        for (long i = - 2; i <= 2; i++) {
            if (i == 0) {
                i++;
            }
            for (long j = - 2; j <= 2; j++) {
                if (j == 0) {
                    j++;
                }
                if (abs(i) == abs(j)) {
                    continue;
                }

                long new_i = i_cur + i;
                long new_j = j_cur + j;

                if (new_i < n && new_i >= 0 && new_j < m && new_j >= 0) {
                    if (visited[new_i][new_j])
                        continue;

                    visited[new_i][new_j] = true;
                    dist[new_i][new_j] = dist[i_cur][j_cur] + 1;
                    top_queue.push(make_pair(new_i, new_j));


                    if (new_i == x && new_j == y) {
                        cout << dist[new_i][new_j];
                        return 0;
                    }

                }

            }
        }
    }

    cout << "NEVAR";
    return 0;
}



