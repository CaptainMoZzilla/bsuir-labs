//
// Created by andrew on 5/27/20.
//
#include <bits/stdc++.h>

using namespace std;

struct BasisNode {
    int x, y;
};

bool check_volume(vector<vector<int>>& matrix,
                  vector<int>& A_vec,
                  vector<int>& B_vec) {
    for(int i = 0; i < A_vec.size(); ++i) {
        for(int j = 0; j < B_vec.size(); ++j) {
        }
    }
}


void print_vector(vector<BasisNode>& vec) {
    for(unsigned int j = 0; j < vec.size(); j++) {
        cout << "(" << vec[j].x << ", " << vec[j].y << ") ";
    }
    cout << "\n";
}

// (1, 6) (1, 3) (2, 3) (2, 5) (3, 5) (3, 6)

void print_vector(vector<int>& vec) {
    for(unsigned int j = 0; j < vec.size(); j++) {
        cout << vec[j] << " ";
    }
        cout << "\n";
}

void print_matrix(vector<vector<int>>& matrix) {
    for(unsigned int i = 0; i < matrix.size(); i++) {
        for(unsigned int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}
tuple<vector<vector<int>>, vector<BasisNode>> north_west_angle(vector<int> &A_vec,
                                                               vector<int> &B_vec) {
    vector<vector<int>> res(A_vec.size(), vector<int>(B_vec.size()));
    vector<BasisNode> basis;
    vector<int> A_copy = A_vec,
            B_copy = B_vec;

    int min_current;
    int i = 0, j = 0;

    while (basis.size() != A_vec.size() + B_vec.size() - 1) {
        auto min_val = std::min(A_copy[i], B_copy[j]);
        A_copy[i] -= min_val;
        B_copy[j] -= min_val;

        res[i][j] = min_val;

        BasisNode node = {
                .x = i,
                .y = j
        };
        basis.push_back(node);

        if (A_copy[i] == 0 && i < A_copy.size() - 1) {
            i++;
        } else if (B_copy[j] == 0 && j < B_copy.size() - 1) {
            j++;
        }
    }
    return make_tuple(res, basis);

}



#define SEARCH_BY_ROW 1
#define SEARCH_BY_COLUMN 2
#define VISITED -1
tuple<vector<int>, vector<int>> calculate_potentials(vector<vector<int>>& C,
                                                     vector<BasisNode>& basis) {
    vector<tuple<int, int>> q;
    vector<int> U(C.size()),
                V(C[0].size()),
                U_visited(C.size()),
                V_visited(C[0].size());

    V[V.size() - 1] = 0;
    V_visited[V.size() - 1] = VISITED;
    q.push_back(make_tuple(SEARCH_BY_COLUMN, V.size() - 1));

    while(q.size()) {
        auto [flag, index] = q.back();
        q.pop_back();

        if(flag == SEARCH_BY_COLUMN) {
            for(int i = 0; i < basis.size(); ++i) {
                auto node = basis[i];
                if (node.y == index && U_visited[node.x] != VISITED) {
                    U[node.x] = C[node.x][node.y] - V[node.y];
                    U_visited[node.x] = VISITED;
                    q.push_back(make_tuple(SEARCH_BY_ROW, node.x));
                }
            }
        } else if (flag == SEARCH_BY_ROW){
            for(int i = 0; i < basis.size(); ++i) {
                auto node = basis[i];
                if (node.x == index && V_visited[node.y] != VISITED) {
                    V[node.y] = C[node.x][node.y] - U[node.x];
                    V_visited[node.y] = VISITED;
                    q.push_back(make_tuple(SEARCH_BY_COLUMN, node.y));
                }
            }
        }
    }
    return make_tuple(U, V);
}

tuple<vector<vector<int>>, tuple<int, int>> create_plan_and_get_min_el_indices(vector<int>& U,
                                                                               vector<int>& V,
                                                                               vector<vector<int>>& C,
                                                                               vector<BasisNode>& basis) {
    vector<vector<int>> res(U.size(), vector<int>(V.size()));
    int minimal = 2147483647;
    tuple<int, int> indices;

//    vector<vector<bool>> Apochimy(U.size(), vector<bool>(V.size()));
//    for(int i = 0; i < basis.size(); ++i) {
//        auto node = basis[i];
//        Apochimy[node.x][node.y] = true;
//    }


    for(int i = 0; i < U.size(); ++i) {
        for(int j = 0; j < V.size(); ++j) {
//            if(!Apochimy[i][j]) {
                res[i][j] = C[i][j] - U[i] - V[j];
                if(res[i][j] < minimal) {
                    minimal = res[i][j];
                    indices = make_tuple(i, j);
                }
//            }
        }
    }
    return make_tuple(res, indices);
}


bool is_optimal(tuple<int, int>& indices, vector<vector<int>>& C) {
    return C[get<0>(indices)][get<1>(indices)] >= 0;
}

vector<BasisNode> find_loop(vector<BasisNode>& basis, int rows, int columns) {
    vector<int> use_element(basis.size());
    vector<int> rows_values_count(rows),
                columns_values_count(columns);

    for(int i = 0; i < basis.size(); ++i) {
        auto node = basis[i];
        rows_values_count[node.x]++;
        columns_values_count[node.y]++;
    }

    while(true) {
        bool checker = false;
        for(int i = 0; i < rows_values_count.size(); ++i) {
            if (rows_values_count[i] == 1) {
                for (int j = 0; j < basis.size(); ++j) {
                    if (basis[j].x == i &&  use_element[j] != -1) {
                        rows_values_count[basis[j].x]--;
                        columns_values_count[basis[j].y]--;
                        use_element[j] = -1;
                        break;
                    }
                }
            }
        }
        for(int i = 0; i < columns_values_count.size(); ++i) {
            if (columns_values_count[i] == 1) {
                for (int j = 0; j < basis.size(); ++j) {
                    if (basis[j].y == i && use_element[j] != -1) {
                        rows_values_count[basis[j].x]--;
                        columns_values_count[basis[j].y]--;
                        use_element[j] = -1;
                        checker = true;
                        break;
                    }
                }
            }
        }

        if(!checker) {
            break;
        }
    }

    vector<BasisNode> loop;
    for(int i = 0; i < basis.size(); ++i) {
        if(use_element[i] != -1) {
            loop.push_back(basis[i]);
        }
    }
    return loop;
}


bool compare_by_columns(const tuple<int, BasisNode> &a, const tuple<int, BasisNode> &b)
{
    auto [aIndex, aNode] = a;
    auto [bIndex, bNode] = b;

    return aNode.y < bNode.y;
}


bool compare_by_rows(const tuple<int, BasisNode>& a, const tuple<int, BasisNode> &b)
{
    auto [aIndex, aNode] = a;
    auto [bIndex, bNode] = b;

    return aNode.x < bNode.x;
}


vector<BasisNode> order_loop(vector<BasisNode>& loop, tuple<int, int>& root_node) {
    vector<BasisNode> ordered_loop;
    vector<bool> is_used(loop.size());

    // Думаю тут всё и посыпится
    for(int i = 0; i < loop.size(); ++i) {
        auto tmp = loop[i];
        if(tmp.x == get<0>(root_node) && tmp.y == get<1>(root_node)) {
            ordered_loop.push_back(tmp);
            is_used[i] = true;
            break;
        }
    }

    for(int i = 1; i < loop.size(); ++i) {
        vector<tuple<int, BasisNode>> temp_vector;
        auto current_node = ordered_loop[ordered_loop.size() - 1];
        temp_vector.push_back(make_tuple(-1, current_node));

        if(i % 2 == 0) { // Ищу в строке
            for(int j = 0; j < loop.size(); ++j) {
                if(!is_used[j]) {
                    auto compare_node = loop[j];
                    if(current_node.x == compare_node.x) {
                        temp_vector.push_back(make_tuple(j, compare_node));
                    }
                }
            }
            sort(temp_vector.begin(), temp_vector.end(), compare_by_columns);
        } else { // Ищу в столбце
            for(int j = 0; j < loop.size(); ++j) {
                if(!is_used[j]) {
                    auto compare_node = loop[j];
                    if(current_node.y == compare_node.y) {
                        temp_vector.push_back(make_tuple(j, compare_node));
                    }
                }
            }
            sort(temp_vector.begin(), temp_vector.end(), compare_by_rows);
        }

        if(temp_vector.size() == 1) {
            ordered_loop.push_back(current_node);
            continue;
        }

        for(int j = 0; j < temp_vector.size(); ++j) {
            auto [index, sorted_node] = temp_vector[j];
            if((sorted_node.x == current_node.x) && (sorted_node.y == current_node.y)) {
                if((j % 2 == 0)) {
                    auto [idx, value] = temp_vector[j + 1];
                    ordered_loop.push_back(value);
                    is_used[idx] = true;

                } else {
                    auto [idx, value] = temp_vector[j - 1];
                    ordered_loop.push_back(value);
                    is_used[idx] = true;
                }
                break;
            }
        }
    }
    return ordered_loop;
}


void update_plan(vector<vector<int>>& C,
                 vector<BasisNode>& basis,
                 vector<BasisNode>& loop,
                 tuple<int, int>& new_node) {

    C[get<0>(new_node)][get<1>(new_node)] = 0;

    tuple<int, int> min_indices;
    int minimal = 2147483647;

    //Найдем минимальный элемент
    for(int i = 1; i < loop.size(); i += 2) {
        auto node = loop[i];
        if(C[node.x][node.y] < minimal) {
            min_indices = make_tuple(node.x, node.y);
            minimal = C[node.x][node.y];
        }
    }
    //cout << "\nINDEX TO DROP: " << get<0>(min_indices) << " " << get<1>(min_indices) << endl;

    for(int i = 0; i < loop.size(); ++i) {
        auto node = loop[i];
        if(i % 2 == 0) {
            C[node.x][node.y] += minimal;
        } else {
            C[node.x][node.y] -= minimal;
        }
    }

    for(int i = 0; i < basis.size(); ++i) {
        auto node = basis[i];
        if(node.x == get<0>(min_indices) && node.y == get<1>(min_indices)) {
            //cout << "\nINDEX TO DROP: " << node.x << " " << node.y << endl;
            basis.erase(basis.begin() + i);
            //cout << "\nBasis after erase: \n";
            //print_vector(basis);
            break;
        }
    }
}


void potential_method(vector<vector<int>>& C, vector<int>& A_vec, vector<int>& B_vec) {
    int sum_A_vec = 0;
    for(int i = 0; i < A_vec.size(); ++i) {
        sum_A_vec += A_vec[i];
    }

    int sum_B_vec = 0;
    for(int i = 0; i < B_vec.size(); ++i) {
        sum_B_vec += B_vec[i];
    }

    bool new_column = false, new_row = false;
    if(sum_A_vec > sum_B_vec) {
        B_vec.push_back(sum_A_vec - sum_B_vec);
        for(int i = 0; i < C.size(); ++i) {
            C[i].push_back(0);
        }
        new_column = true;
    } else if(sum_B_vec > sum_A_vec) {
        A_vec.push_back(sum_B_vec - sum_A_vec);
        C.push_back(vector<int>(C[0].size(), 0));
        new_row = true;
    }
    //cout << "\nC matrix:\n";
    //print_matrix(C);


    auto [plan, basis] = north_west_angle(A_vec, B_vec);

    //cout << "\nInit plan:\n";
    //print_matrix(plan);

    //cout << "\nInit basis:\n";
    //print_vector(basis);
    while(true){
    //for(int i = 0; i < INT32_MAX; ++i) {
        //cout << "\n############################ " << i << " ############################\n";

        auto [U, V] = calculate_potentials(C, basis);

        //cout << "\nU vector: \n";
        //print_vector(U);

        //cout << "\nV vector: \n";
        //print_vector(V);

        auto [potential_matrix, indices] = create_plan_and_get_min_el_indices(U, V, C, basis);
        //cout << "\nPatential matrix: \n";
        //print_matrix(potential_matrix);
        //cout << "\nMinimal el indices x: "<< get<0>(indices) << " y: "<< get<1>(indices) << "\n";

        if(is_optimal(indices, potential_matrix)) {
            if(new_row) {
                plan.pop_back();
            } else if(new_column) {
                for(int a = 0; a < plan.size(); ++a) {
                    plan[a].pop_back();
                }
            }

            ////cout << "\n";
            print_matrix(plan);
            exit(0);
        }

        BasisNode node = {
                .x = get<0>(indices),
                .y = get<1>(indices)
        };
        basis.push_back(node);

        int size = B_vec.size();
        int sizeA = A_vec.size();
        auto loop = find_loop(basis, sizeA, size);

        //cout << "\nUnordered Loop: \n";
        //print_vector(loop);


        auto ordered_loop = order_loop(loop, indices);
        //cout << "\nOrdered loop: \n";
        //print_vector(ordered_loop);

        update_plan(plan, basis, ordered_loop, indices);
        //cout << "\nUpdated plan:\n";
        //print_matrix(plan);

        //cout << "\nUpdated basis:\n";
        //print_vector(basis);
    }
    if(new_row) {
        plan.pop_back();
    } else if(new_column) {
        for(int a = 0; a < plan.size(); ++a) {
            plan[a].pop_back();
        }
    }

    ////cout << "\n";
    print_matrix(plan);
    exit(0);

}


int main() {
    int rows, columns;
    cin >> rows >> columns;

    vector<vector<int>> C(rows, vector<int>(columns));
    vector<int> A_vec(rows), B_vec(columns);

    bool b_is_all_zero = true;
    bool a_is_all_zero = true;


    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cin >> C[i][j];
        }
    }

    for(int i = 0; i < rows; i++) {
        cin >> A_vec[i];
        if(A_vec[i] != 0) {
            a_is_all_zero = false;
        }
    }

    for(int i = 0; i < columns; i++) {
        cin >> B_vec[i];
        if(B_vec[i] != 0) {
            b_is_all_zero = false;
        }
    }

    if(a_is_all_zero || b_is_all_zero) {
        for(int a = 0; a < rows; ++a) {
            for(int b = 0; b < columns; ++b) {
                cout << 0 << " ";
            }
            cout << "\n";
        }
        exit(0);
    }
    
    potential_method(C, A_vec, B_vec);

    return 0;
}

// NORTH WEST TUTUTU
/*
3 4
2 3 2 4
3 2 5 1
4 3 2 6
30 40 20
20 30 30 10
*/
/*
3 4
30 40 20
30 20 30 10
*/
