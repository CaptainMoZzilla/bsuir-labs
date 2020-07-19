#include <stdlib.h>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

void print_matrix(vector<vector<double>>& matrix) {
    for(unsigned int i = 0; i < matrix.size(); i++) {
        for(unsigned int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}


void print_vector(vector<double>& vec) {
    for(unsigned int j = 0; j < vec.size(); j++) {
        cout << setprecision(10) << vec[j] << " ";
    }
    // cout << "\n";
}

vector<vector<double>> diag(int size) {
    vector<vector<double>> res(size, vector<double>(size));
    for(int i = 0; i < size; ++i)
        res[i][i] = 1.0;
    return res;
}


vector<vector<double>> mul(vector<vector<double>>& v1, vector<vector<double>>& v2) {
    auto size = v1.size();
    vector<vector<double>> res(size, vector<double>(size));

    for(unsigned int i = 0; i < size; ++i) {
        for(unsigned int j = 0; j < size; ++j) {
            for(unsigned int k = 0; k < size; k++) {
                res[i][j] += v1[i][k] * v2[k][j];
            }
        }
    }
    return res;
}


vector<double> mul(vector<double> vec, vector<vector<double>>& matrix) {
    auto rows = matrix.size(),
            columns = matrix[0].size();
    vector<double> res(columns);

    for(unsigned int i = 0; i < columns; ++i) {
        for(unsigned int j = 0; j < rows; ++j) {
            res[i] += matrix[j][i] * vec[j];
        }
    }
    return res;
}


vector<double> mul(vector<vector<double>>& matrix, vector<double>& vec) {
    auto size = matrix.size();
    vector<double> res(size);

    for(unsigned int i = 0; i < size; ++i) {
        for(unsigned int j = 0; j < size; ++j) {
            res[i] += matrix[i][j] * vec[j];
        }
    }
    return res;
}


vector<vector<double>> inv(vector<vector<double>>& A) {

    int rows = A.size(), columns = A[0].size();
    vector<vector<double>> A_tmp = A; //(rows, vector<double>(columns));
    // copy(A.begin(), A.end(), back_inserter(A_tmp));

    auto result = diag(columns);

    for(unsigned int i = 0, j = 0; i < rows, j < rows; ++i, ++j) {
        unsigned int k = j;
        for(unsigned int temp_id = j; temp_id < rows; ++temp_id) {
            if(abs(A_tmp[temp_id][i])  > abs(A_tmp[k][i])) {
                k = temp_id;
            }
        }

        swap(A_tmp[j], A_tmp[k]);
        swap(result[j], result[k]);

        for(int temp_id = 0; temp_id < rows; ++temp_id) {
            if(temp_id != j) {
                double coefficient = A_tmp[temp_id][i] / A_tmp[j][i];
                for(int r = 0; r < rows; r++) {
                    A_tmp[temp_id][r] -= A_tmp[j][r] * coefficient;
                    result[temp_id][r] -= result[j][r] * coefficient;
                }
            }
        }
    }
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < rows; ++j) {
            if (result[i][j] != 0) {
                result[i][j] /= A_tmp[i][i];
            }
        }
    }
    return result;
}


void mul_by_const(vector<double>& vec, double val) {
    for(unsigned int i = 0; i < vec.size(); ++i) {
        vec[i] *= val;
    }
}


void change_column(vector<vector<double>>& matrix,
                   vector<double>& new_vec,
                   int index) {
    for(unsigned int i = 0; i < matrix.size(); ++i) {
        matrix[i][index] = new_vec[i];
    }
}


vector<double> get_basis(vector<double>& vec, vector<int> indices) {
    int size = indices.size();
    vector<double> res(size);

    for(int i = 0; i < size; ++i) {
        res[i] = vec[indices[i]];
    }
    return res;
}


vector<vector<double>> get_basis(vector<vector<double>>& matrix, vector<int>& indices) {
    int size = indices.size();
    vector<vector<double>> res(size, vector<double>(size));

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            res[i][j] = matrix[i][indices[j]];
        }
    }
    return  res;
}


vector<double> get_column(vector<vector<double>>& matrix, int index) {
    vector<double> res(matrix.size());
    for(unsigned int i = 0; i < matrix.size(); ++i) {
        res[i] = matrix[i][index];
    }
    return res;
}


vector<vector<double>> sherman(vector<vector<double>>& B,
                               vector<double>& X,
                               int index) {
    auto l = mul(B, X);
    double temp_l = l[index];
    l[index] = -1.0;
    mul_by_const(l, -1.0 / temp_l);

    auto B_copy = B;
    for(int i = 0; i < X.size(); ++i) {
        for(int j = 0; j < X.size(); ++j) {
            B_copy[j][i] = l[j] * B[index][i];
            if(j != index) {
                B_copy[j][i] += B[j][i];
            }
        }
    }

//    auto M = diag(l.size());
//    change_column(M, l, index);

    return B_copy;//mul(M, B);
}


vector<double> simplex_method(vector<vector<double>>& A,
                              vector<double>& B,
                              vector<double>& C,
                              vector<double>& X,
                              vector<int>& J_B) {

    auto A_basis = get_basis(A, J_B);
    auto A_inv = inv(A_basis);
    int rows = A.size(), columns = A[0].size();

    while(true) {
        int J0 = 0;
        auto C_B = get_basis(C, J_B);
        auto U = mul(C_B, A_inv);
        auto delta = mul(U, A);

        bool checker = false;

        for(int i = 0; i < columns; ++i) {
            double tmp = delta[i] - C[i];
            if((tmp < 0.0) && (fabs(tmp) > 1e-6)) {
                J0 = i;
                checker = true;
                break;
            }
        }
        if(!checker) {
            cout << "Bounded\n";
            break;
        }

        auto A_column = get_column(A, J0);
        auto Z = mul(A_inv, A_column);

        unsigned int count = 0;
        for(unsigned int i = 0; i < Z.size(); ++i) {
            count += Z[i] <= 0.0;
        }

        if(count == Z.size()) {
            cout << "Unbounded";
            exit(0);
        }

        vector<double> theta(rows);
        for(unsigned int i = 0; i < Z.size(); ++i) {
            if(Z[i] > 0.0) {
                theta[i] = X[J_B[i]] / Z[i];
            } else {
                theta[i] = numeric_limits<double>::max();
            }
        }

        int S0 = min_element(theta.begin(), theta.end()) - theta.begin();
        J_B[S0] = J0;


        for(int i = 0; i < columns; ++i) {
            auto position = find(J_B.begin(), J_B.end(), i);
            if (position != J_B.end()) {
                if(i == J0) {
                    X[i] = theta[S0];
                } else {
                    int idx = position - J_B.begin();
                    X[i] -= theta[S0] * Z[idx];
                }
            } else {
                X[i] = 0.0;
            }
        }
        auto B_temp = get_column(A, J0);
        A_inv = sherman(A_inv, B_temp, S0);
    }
    return X;
}

int main() {
    int rows, columns;
    cin >> rows >> columns;

    vector<vector<double>> A(rows, vector<double>(columns));
    vector<double> B(rows), C(columns), X(columns);
    vector<int> J_B(rows);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cin >> A[i][j];
        }
    }

    for(int i = 0; i < rows; i++) {
        cin >> B[i];
    }

    for(int i = 0; i < columns; i++) {
        cin >> C[i];
    }

    for(int i = 0; i < columns; i++) {
        cin >> X[i];
    }

    for(int i = 0; i < rows; i++) {
        cin >> J_B[i];
        J_B[i]--;
    }

    auto X_new = simplex_method(A, B, C, X, J_B);
    print_vector(X_new);


    return 0;
}

/*
3 8
-2 -1 3 -7.5 0 0 0 2
4 2 -6 0 1 5 -1 -4
1 -1 0 -1 0 3 1 1
1 1 1
-6 9 -5 2 -6 0 1 3
0 0 0 5 4 0 0 7
4 5 8
*/

/*
3 8
2 -1 1 -7.5 0 0 0 2
4 2 -1 0 1 5 -1 -4
1 -1 1 -1 0 3 1 1
1 1 1
-6 -9 -5 2 -6 0 1 3
4 0 6 0 4 0 0 0
1 3 5
*/

/*
3 8
0 -1 1 -7.5 0 0 0 2
0 2 1 0 -1 3 -1.5 0
1 -1 1 -1 0 3 1 1
1 1 1
-6 -9 -5 2 -6 0 1 3
4 0 6 0 4.5 0 0 0
1 3 5
*/

/*
3 8
-2 -1 1 -7 0 0 0 2
4 2 -1 0 1 5 -1 -5
1 11 0 1 0 3 1 1
1 1 1
6 -9 5 -2 6 0 -1 3
4 0 6 0 4 0 0 0
1 2 3
*/
