#pragma optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>

using namespace std;

const int SIZE = 10000;
bool visited[SIZE];
vector<int> elements[SIZE];
int endPoint = 0, result = 0;



void dfs(int index) {
    if (!visited[index]) {
        //cout << "IN" << index << endl;
        visited[index] = true;

        for (auto a : elements[index]) {
            dfs(a);
        }
    }
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

    int reb_count;
    cin >> endPoint;

    for (int a = 0; a < endPoint; a++)
        visited[a] = false;

    cin >> reb_count;

    int a, b;
    for (int ASD = 0; ASD < reb_count; ASD++) {
        cin >> a >> b;
        b--;
        a--;

        elements[a].push_back(b);
        elements[b].push_back(a);
    }

    for (int c = 0; c < endPoint; c++) {
        if (!visited[c]) {
            //cout << "Test";
            dfs(c);
            result++;
        }
    }

    cout << --result;

    return 0;
}

