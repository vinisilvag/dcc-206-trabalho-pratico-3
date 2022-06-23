// 2021421869 - Vinicius Silva Gomes

#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'

#define f first
#define s second
#define pb push_back

pair<int, int> find_largest_table(int n, int m, vector<vector<int>> &house, int k, vector<pair<int, int>> &tables);

int main() { _
    int n, m, k;

    cin >> n >> m;

    vector<vector<int>> house(n, vector<int>(m));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char cell;

            cin >> cell;

            if(cell == '*') house[i][j] = 0;
            else house[i][j] = 1;
        }
    }

    cin >> k;

    vector<pair<int, int>> tables(k);

    for(int i = 0; i < k; i++){
        int width, height;

        cin >> width >> height;

        tables[i] = { width, height };
    }

    pair<int, int> largest_table = find_largest_table(n, m, house, k, tables);

    cout << largest_table.f << " " << largest_table.s << endl;

    return 0;
}

pair<int, int> find_largest_table(int n, int m, vector<vector<int>> &house, int k, vector<pair<int, int>> &tables) {
    vector<vector<int>> dp(n, vector<int>(m));
    pair<int, int> rec_dimensions = { 0, 0 };
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0) {
                dp[i][j] = house[i][j];
            } else {
                if(house[i][j] == 0) dp[i][j] = 0;
                else dp[i][j] = dp[i-1][j] + house[i][j];
            }
        }

        int area = 0, left = -1, right = -1;

        for(int j = 0; j < m; j++) {
            // TODO: calc rectangle dimensions

            area = (right - left + 1) * dp[i][j];

            if(area >= (rec_dimensions.f * rec_dimensions.s)) {
                rec_dimensions.f = (right - left + 1);
                rec_dimensions.s = dp[i][j];
            }
        }
    }

    vector<pair<int, int>> areas(k);

    for(int i = 0; i < k; i++) {
        areas[i].f = tables[i].f * tables[i].s;
        areas[i].s = i;
    }

    sort(areas.begin(), areas.end(), greater<pair<int, int>>());

    for(int i = 0; i < k; i++) {
        
    }

    return { 0, 0 };
}