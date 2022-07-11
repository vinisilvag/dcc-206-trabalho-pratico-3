// 2021421869 - Vinicius Silva Gomes

#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'

#define f first
#define s second
#define pb push_back

// Verifica se uma mesa cabe nas dimensões informadas como parâmetros
bool table_fits(pair<int, int> dimensions, pair<int, int> table);

/*
    Ordena de maneira decrescente um vetor de pares (mesas) a partir da multiplicação do par (área)
    e a partir da segunda coordenada (largura)
*/
bool sort_by_area_and_width(const pair<int,int> &a, const pair<int,int> &b);

// Intercala mesas e áreas ordenadas, selecionando a maior mesa possível dado esse conjunto de áreas
pair<int, int> interpolate_tables_and_areas(int k, vector<pair<int, int>> &areas, vector<pair<int, int>> &ordered_tables);

/*
    Encontra todas as áreas possíveis na planta da casa e chama o método interpolate_tables_and_areas
    para identificar qual a maior mesa que cabe nessas áreas, retornando essa mesa ao final
*/
pair<int, int> find_largest_table(int n, int m, vector<vector<int>> &house, int k, vector<pair<int, int>> &tables);

int main() { _
    int n, m, k;

    // Lê as dimensões da planta
    cin >> n >> m;

    // Declara a planta da casa
    vector<vector<int>> house(n, vector<int>(m));

    // Lê a planta da casa, binarizando os caracteres: # = 0 e . = 1
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

    // Lê o vetor de mesas escolhidas pela Tia
    for(int i = 0; i < k; i++) {
        int length, width;

        cin >> length >> width;

        tables[i] = { length, width };
    }

    // Encontra a melhor mesa para essa instância do problema
    pair<int, int> largest_table = find_largest_table(n, m, house, k, tables);

    // Exibe as dimensões dessa mesa
    cout << largest_table.f << " " << largest_table.s << endl;

    return 0;
}

bool table_fits(pair<int, int> dimensions, pair<int, int> table) {
    // Verifica se a mesa cabe nas dimensões, comparando tanto em sua orientação original quanto rotacionada 90 graus
    if(table.f <= dimensions.f and  table.s <= dimensions.s) return true;
    else if(table.s <= dimensions.f and table.f <= dimensions.s) return true;

    return false;
}

bool sort_by_area_and_width(const pair<int,int> &a, const pair<int,int> &b) {
    // Calcula a área das mesas comparadas
    int area_a = a.f * a.s, area_b = b.f * b.s;

    // Compara primeiro pela área e depois pela segunda coordenada (largura)
    if(area_a != area_b) return area_a > area_b;
    else return a.s > b.s;
}

pair<int, int> interpolate_tables_and_areas(int k, vector<pair<int, int>> &areas, vector<pair<int, int>> &ordered_tables) {
    int i = 0, j = 0;

    // Itera pelo número de áreas calculadas e pelo número de mesas
    while(i < int(areas.size()) && j < k) {
        pair<int, int> curr_area = areas[i];
        pair<int, int> curr_table = ordered_tables[j];

        int row_area = curr_area.f * curr_area.s;
        int table_area = curr_table.f * curr_table.s;

        // Verifica se a mesa tem área menor que a da área analisada
        if(row_area >= table_area) {
            if(table_fits(curr_area, curr_table)) {
                // Caso sim e essa mesa caiba também nas dimensões, ela é retornada
                return { curr_table.f, curr_table.s };
            } else {
                // Caso não a próxima área é escolhida
                i++;
            }
        } else {
            // Caso não a próxima mesa é escolhida e a contagem de áreas recomeça
            j++;
            i = 0;
        }
    }

    /*
        Retorna dimensões -1 e -1 caso não exista uma mesa que caiba na planta da casa (situação
        que não está presente nos casos de teste)
    */
    return { -1, -1 };
}

pair<int, int> find_largest_table(int n, int m, vector<vector<int>> &house, int k, vector<pair<int, int>> &tables) {
    // Inicializa o histograma das áreas com todas as coordenadas valendo 0
    vector<vector<int>> histogram(n, vector<int>(m, 0));

    vector<pair<int, int>> areas;
    vector<pair<int, int>> ordered_tables(k);

    // Percorre a matriz calculando o histograma cumulativo
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0) {
                histogram[i][j] = house[i][j];
            } else {
                if(house[i][j] == 0) histogram[i][j] = 0;
                else histogram[i][j] = histogram[i-1][j] + house[i][j];
            }
        }

        // Define uma pilha de posições iniciais dos retângulos
        stack<int> start_pos;

        int k = 0;
        while(k < m) {
            /*
                Se a fila estiver vazia ou a barra atual do histograma é maior que a última barra
                inserida, a posição k é adicionada na pilha para que um novo retângulo comece a ser montado
            */
            if(start_pos.empty() || histogram[i][start_pos.top()] <= histogram[i][k]) {
                start_pos.push(k);
                k++;
            } else {
                // Se não, calcula a área para a iteração atual
                int width = k;
                int length = histogram[i][start_pos.top()]; start_pos.pop();

                if(!start_pos.empty()) {
                    width = k - start_pos.top() - 1;
                }

                // Insere a área no vetor que acumula as áreas calculadas
                areas.pb({ width, length });
            }
        }

        /*
            Repete o processo de cálculo de área caso as k iterações terminem e a pilha
            ainda contenha retângulos não finalizados
        */
        while(!start_pos.empty()) {
            int width = k;
            int length = histogram[i][start_pos.top()]; start_pos.pop();

            if(!start_pos.empty()) {
                width = k - start_pos.top() - 1;
            }

            areas.pb({ width, length });
        }
    }

    // Copia as mesas para outro vetor (para não alterar os dados de entrada do problema diretamente)
    for(int i = 0; i < k; i++) {
        ordered_tables[i] = { tables[i].f, tables[i].s };
    }

    // Ordena as áreas encontradas e as mesas
    sort(ordered_tables.begin(), ordered_tables.end(), sort_by_area_and_width);
    sort(areas.begin(), areas.end(), sort_by_area_and_width);

    // Intercala as mesas e as áreas e obtém a melhor mesa para essa instância do problema
    pair<int, int> largest_table = interpolate_tables_and_areas(k, areas, ordered_tables);

    // Retorna a mesa obtida
    return largest_table;
}