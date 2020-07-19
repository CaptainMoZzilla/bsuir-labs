#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

void print_matrix(vector<vector<float>>& matrix) {
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix.size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void print_vector(vector<float>& vec) {
    for(int j = 0; j < vec.size(); j++) {
        cout << vec[j] << " ";
    }
    cout << "\n";
}

vector<vector<float>> diag(int size) {
    vector<vector<float>> res(size, vector<float>(size));
    for(int i = 0; i < size; ++i)
        res[i][i] = 1;
    return res;
}

vector<vector<float>> mul(vector<vector<float>>& v1, vector<vector<float>>& v2) {
    auto size = v1.size();
    vector<vector<float>> res(size, vector<float>(size));

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            for(int k = 0; k < size; k++) {
                res[i][j] += v1[i][k] * v2[k][j];
            }
        }
    }
    return res;
}

vector<float> mul(vector<vector<float>>& matrix, vector<float>& vec) {
    auto size = matrix.size();
    vector<float> res(size);

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            res[i] += matrix[i][j] * vec[j];
        }
    }
    return res;
}

void mul_by_const(vector<float>& vec, float val) {
    for(int i = 0; i < vec.size(); ++i) {
        vec[i] *= val;
    }
}

void change_column(vector<vector<float>>& matrix,
                   vector<float>& new_vec,
                   int index) {
    for(int i = 0; i < matrix.size(); ++i) {
        matrix[i][index] = new_vec[i];
    }
}

vector<vector<float>> sherman(vector<vector<float>>& A,
                              vector<vector<float>>& B,
                              vector<float>& X,
                              int index) {
    auto l = mul(B, X);
    float temp_l = l[index];

    if(temp_l == 0) {
        cout << "NO";
        exit(0);
    }
    cout << "YES\n";


    l[index] = -1;
    mul_by_const(l, -1. / temp_l);

    auto M = diag(A.size());
    change_column(M, l, index);

    return mul(M, B);
}

int main() {
    int index, size;
    cin >> size >> index;
    index--;

    vector<vector<float>> A(size, vector<float>(size)),
                          B(size, vector<float>(size));
    vector<float> X(size);

    for(int i = 0; i < size; i++) {
       for(int j = 0; j < size; j++) {
           cin >> A[i][j];
       }
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            cin >> B[i][j];
        }
    }

    for(int i = 0; i < size; i++) {
        cin >> X[i];
    }

    // start processing
    auto res = sherman(A, B, X, index);
    print_matrix(res);


   // cout << "Hello, World!" << std::endl;

    return 0;
}
