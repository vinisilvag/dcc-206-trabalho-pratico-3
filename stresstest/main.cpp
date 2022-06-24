// 2021421869 - Vinicius Silva Gomes

#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'

#define f first
#define s second
#define pb push_back

const int INF = 0x3f3f3f3f;

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

    for(int i = 0; i < k; i++){
        int length, width;

        cin >> length >> width;

        tables[i] = { length, width };
    }

    pair<int, int> largest_table = find_largest_table(n, m, house, k, tables);

    cout << largest_table.f << " " << largest_table.s << endl;

    return 0;
}

bool table_fit(int max_area, pair<int, int> dimensions, pair<int, int> table) {
    if(max_area < table.f * table.s) return false;

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

    stack<int> position_stack, height_stack;
    int max_area = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0) {
                histogram[i][j] = house[i][j];
            } else {
                if(house[i][j] == 0) histogram[i][j] = 0;
                else histogram[i][j] = histogram[i-1][j] + house[i][j];
            }
        }

        for(int k = 0; k < m; k++) {
            int last_width = INF;

            while(!height_stack.empty() && height_stack.top() > histogram[i][k]) {
                last_width = position_stack.top(); position_stack.pop();
                int curr_height = height_stack.top(); height_stack.pop();

                int curr_area = (k - last_width) * curr_height;

                if(curr_area > max_area) {
                    max_area = curr_area;
                    dimensions = { (k - last_width), curr_height };
                }
            }

            if(height_stack.empty() || height_stack.top() < histogram[i][k]) {
                height_stack.push(histogram[i][k]);
                position_stack.push(min(last_width, k));
            }
        }

        while(!height_stack.empty()) {
            int start_pos = position_stack.top(); position_stack.pop();
            int curr_height = height_stack.top(); height_stack.pop();

            int curr_area = (m - start_pos) * curr_height;

            if(curr_area > max_area) {
                max_area = curr_area;
                dimensions = { (m - start_pos), curr_height };
            }
        }
    }

    vector<pair<int, int>> ordered_tables(k);

    for(int i = 0; i < k; i++) {
        ordered_tables[i] = { tables[i].f, tables[i].s };
    }

    sort(ordered_tables.begin(), ordered_tables.end(), sort_by_area_and_width);

    for(int i = 0; i < k; i++)
        if(table_fit(max_area, dimensions, ordered_tables[i]))
            return { ordered_tables[i].f, ordered_tables[i].s };

    return { -1, -1 };
}