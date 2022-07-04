// 2021421869 - Vinicius Silva Gomes

#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'

#define f first
#define s second
#define pb push_back

const int INF = 0x3f3f3f3f;

bool table_fits(pair<int, int> dimensions, pair<int, int> table);

bool sort_by_area_and_width(const pair<int,int> &a, const pair<int,int> &b);

pair<int, int> find_largest_table(int n, int m, vector<vector<int>> &house, int k, vector<pair<int, int>> &tables);

int main() { _
    int n, m, k;

    cin >> n >> m;

    vector<vector<int>> house(n, vector<int>(m));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char cell;

            cin >> cell;

            if(cell == '#') house[i][j] = 0;
            else house[i][j] = 1;
        }
    }

    cin >> k;

    vector<pair<int, int>> tables(k);

    for(int i = 0; i < k; i++) {
        int length, width;

        cin >> length >> width;

        tables[i] = { length, width };
    }

    pair<int, int> largest_table = find_largest_table(n, m, house, k, tables);

    cout << largest_table.f << " " << largest_table.s << endl;

    return 0;
}

bool table_fits(pair<int, int> dimensions, pair<int, int> table) {
    if(table.f <= dimensions.f and  table.s <= dimensions.s) return true;
    else if(table.s <= dimensions.f and table.f <= dimensions.s) return true;

    return false;
}

bool sort_by_area_and_width(const pair<int,int> &a, const pair<int,int> &b) {
    int area_a = a.f * a.s, area_b = b.f * b.s;

    if(area_a != area_b) return area_a > area_b;
    else return a.s > b.s;
}

pair<int, int> find_largest_table(int n, int m, vector<vector<int>> &house, int k, vector<pair<int, int>> &tables) {
    vector<vector<int>> histogram(n, vector<int>(m, 0));
    pair<int, int> dimensions = { 0, 0 };

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0) {
                histogram[i][j] = house[i][j];
            } else {
                if(house[i][j] == 0) histogram[i][j] = 0;
                else histogram[i][j] = histogram[i-1][j] + house[i][j];
            }
        }

        int max_area = 0;
        stack<int> start_pos;

        int k = 0;
        while(k < m) {
            if(start_pos.empty() || histogram[i][start_pos.top()] <= histogram[i][k]) {
                start_pos.push(k); k++;
            } else {
                int curr_length = histogram[i][start_pos.top()]; start_pos.pop();
                int curr_width = (start_pos.empty() ? k : k - start_pos.top() - 1);

                int curr_area = curr_width * curr_length;

                if(curr_area > max_area) {
                    max_area = curr_area;
                    dimensions = { curr_width, curr_length };
                }
            }
        }

        while(!start_pos.empty()) {
            int curr_length = histogram[i][start_pos.top()]; start_pos.pop();
            int curr_width = (start_pos.empty() ? k : k - start_pos.top() - 1);

            int curr_area = curr_width * curr_length;

            if(curr_area > max_area) {
                max_area = curr_area;
                dimensions = { curr_width, curr_length };
            }
        } 
    }

    vector<pair<int, int>> ordered_tables(k);

    for(int i = 0; i < k; i++) {
        ordered_tables[i] = { tables[i].f, tables[i].s };
    }

    sort(ordered_tables.begin(), ordered_tables.end(), sort_by_area_and_width);

    for(int i = 0; i < k; i++)
        if(table_fits(dimensions, ordered_tables[i]))
            return { ordered_tables[i].f, ordered_tables[i].s };

    return { -1, -1 };
}