#include <bits/stdc++.h>

using namespace std;

const long SIZE = 100000;

vector<pair<long,long>> elements[SIZE];
priority_queue<pair<long, long>> top_queue;
bool visited[SIZE];
long distances[SIZE];
long top_count = 0;

void deijkstra() {
    while(!top_queue.empty()) {
        long top = top_queue.top().second;
        top_queue.pop();

        if (!visited[top]) {
            visited[top] = true;

            for (auto a : elements[top]) {
                long diff = a.second, new_top = a.first;


                long new_distance = distances[top] + diff;


                //cout << endl << "TOP: " << new_top;
                if (new_distance < distances[new_top]) {
                    distances[new_top] = new_distance;
                    top_queue.push(make_pair((-1 * distances[new_top]), new_top));
                }

            }
        }

    }
}

void show_distances() {

    for (long temp = 0; temp < top_count; temp++) {
        cout << endl << temp << " " << distances[temp];
    }

}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    long reb_count;
    long a, b, c;
    long begin_, end_;

    cin >> top_count >> reb_count;

    for (long temp = 0; temp < top_count; temp++) {
        visited[temp] = false;
        distances[temp] = LONG_MAX;
    }

    for (long temp = 0; temp < reb_count; temp++) {
        cin >> a >> b >> c;

        a--;
        b--;


        //cout << "Index: " << a << b << endl;
        elements[a].push_back(make_pair(b, c));
        elements[b].push_back(make_pair(a, c));
    }



    cin >> begin_ >> end_;
    begin_--;
    end_--;

    //cout << "Index: " << begin_ << end_ << endl;


    distances[begin_] = 0;
    top_queue.push(make_pair(0, begin_));
    deijkstra();

    cout << distances[end_];
    //show_distances();
    return 0;
}


