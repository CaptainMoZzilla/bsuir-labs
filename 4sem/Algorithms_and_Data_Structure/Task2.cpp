#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long c, n;
    vector<long long> vec;

    cin >> n;
    for ( ;n>0; n--) {
        cin >> c;
        vec.push_back(c);
    }

    sort(vec.begin(), vec.end());
    cout << (vec[0] * vec[1] > vec[vec.size() -1 ] *
            vec[vec.size() - 2] ? vec[0] * vec[1] :
            vec[vec.size() -1 ] * vec[vec.size() - 2]);


    return 0;
}
