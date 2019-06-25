#include <bits/stdc++.h>


using namespace std;

long long counter = 0;

vector<long> Msort(vector<long> vec) {
    if (vec.size() < 2)
        return vec;

    int midle = vec.size() / 2;

    vector<long> left(vec.begin (), vec.begin() + midle);
    vector<long> right(vec.begin() + midle, vec.end());

    //cout << left.size() << "   " << right.size() << endl;
    //cin >> counter;

    left = Msort(left);
    right = Msort(right);

   // cout << "sad";

    for (int i = 0, left_INDEX = 0, right_INDEX = 0; i < vec.size(); i++) {
        if (right_INDEX == right.size()) {
            vec[i] = left[left_INDEX];
            left_INDEX++;

        } else if (left_INDEX == left.size()) {
            vec[i] = right[right_INDEX];
            right_INDEX++;

        } else if (left[left_INDEX] <=  right[right_INDEX]) {
            vec[i] = left[left_INDEX];
            left_INDEX++;
        } else {
            counter += left.size() - left_INDEX;
            vec[i] =  right[right_INDEX];
            right_INDEX++;
        }
    }

    return vec;
}

int main()
{
    long long counter1, counter2;
    cin >> counter1;

    counter2 = counter1;
    vector<long> array;

    long temp;

    while (counter1--) {
        cin >> temp;
        array.push_back(temp);
    }

    Msort(array);

    cout << counter;
    return 0;
}

