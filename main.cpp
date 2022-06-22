// 2021421869 - Vinicius Silva Gomes

#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'

#define f first
#define s second
#define pb push_back

int main() { _
    int n, m, k;

    // Lê as dimensões da casa
    cin >> n >> m;

    // Declara a matriz da casa
    vector<vector<char>> house(n, vector<char>(m));

    // Preenche a matriz com a configuração da casa
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> house[i][j];
        }
    }

    cin >> k;

    // Declara o vetor de mesas e lê o tamanho e a largura de cada mesa disponível
    vector<pair<int, int>> table(k);

    for(int i = 0; i < k; i++) {
        int width, length;

        cin >> width >> length;

        table[i] = { width, length };
    }

    return 0;
}

