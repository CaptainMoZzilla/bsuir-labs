#pragma optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;

const long SIZE = 1000000;
long max_len;
long indexes[SIZE];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    string line;
    cin >> line;

    max_len = line.length();
    long count, a, b;
    cin >> count;

    for (long c = 0; c <= max_len; c++)
        indexes[c] = 0;

    while (count--) {
        cin >> a;
        cin >> b;

        if (a > b) {
            long c = a;
            a = b;
            b = c;
        }

        a--;

        indexes[a]++;

        if (b != max_len)
            indexes[b] ++;
    }

    long sum = 0;

    for (long c = 0; c < max_len; c++) {
        sum += indexes[c];

        char temp = line[c];

        if ((sum % 2) != 0) {
            if (temp >= 97 && temp <= 122)
                cout << (char) (temp - 32);
            else
                cout << (char) (temp + 32);
        } else {
            cout << temp;
        }

    }

    return 0;
}
