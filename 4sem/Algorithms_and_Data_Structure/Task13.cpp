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

    if (result > 2) {
        cout << -1;
        return 0;
    }

    cout << reb_count + 1 - endPoint;
    return 0;
}

