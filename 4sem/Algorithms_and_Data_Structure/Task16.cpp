#include <bits/stdc++.h>

using namespace std;

int main()
{

    vector<int> vec;

    string c;
    cin >> c;

    const char* str2 = c.c_str();

    for (int a = 0; a < c.length(); a++) {
        vec.push_back(str2[a] - '0');

    }

    if (next_permutation(vec.begin(), vec.end())) {
        for (auto a : vec)
            cout << a;
    } else {
        cout << -1;
    }

    return 0;
}
