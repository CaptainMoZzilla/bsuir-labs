#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main()
{
    string str;
    cin >> str;

    if (str[str.length() -1] == '0')
        cout << "NO";
    else
        cout  <<str[str.length() -1];
}
