#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

#define MAX_COST 2e+9

struct vertex{
    vertex(){}
};

class Graph{
    int n; // Number of vertices ≤ 10^5
public:
    vector<vertex> V;
    vector<vector<int>> E; // матрица весов
    void add_edge(pair<int, int> p, int &w){E[p.first-1][p.second-1] = w;}
    Graph(int nn);

    vector<int> neighbours(int v);

    void printE();

    int Dijkstra(int &s, int &t);
};

Graph::Graph(int nn){
    n = nn;
    vector<vertex> VV(n, vertex());
    V=VV;
    vector<vector<int> > EE(n, vector<int>(n, -1) );
    E=EE;
}

vector<int> Graph::neighbours(int v){
    vector<int> neigh;
    for(size_t j = 0; j < n; ++j){
        if(E[v][j] != -1){neigh.push_back(j);}
    }
    return neigh;
}

int Graph::Dijkstra(int &s, int &t){
    //queue<int> q;
    vector<int> d(n, MAX_COST);
    d[s-1] = 0;
    vector<bool> touched(n, false);
    for(int i = 0; i < n; ++i)
    {
        int MIN = MAX_COST;
        int v = -1;
        for(int j = 0; j < n; ++j)
        {
            if(!touched[j])
            {
                if (d[j] < MIN)
                {
                    MIN = d[j];
                    v = j;
                }
            }
        }
        if (v == -1) // значит до этой вершины нельзя попасть из вершины s. Если начались такие вершины, то все,
                     // до которых дойти было можно, уже закончились и можно выходить из поиска
            break;
        touched[v] = true;
        for(auto u : neighbours(v))
        {
            if (d[v] +  E[v][u] < d[u])
                d[u] = d[v] + E[v][u];
        }
    }
    if (d[t-1] != MAX_COST)
        return d[t-1];
    else
        return -1;
}


void Graph::printE(){
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < n; ++j){
            cout << E[i][j];
            cout << " ";
        }
        cout << "\n";
    }
}

int main ()
{
    std::ios_base::sync_with_stdio(false);std::cin.tie(0);
    int n, s, t;
    int w;
    cin >> n >> s >> t;

    Graph G(n);

    for(int i = 1; i < n+1; ++i)
    {
        for(int j = 1; j < n+1; ++j)
        {
            cin >> w;
            G.add_edge(make_pair(i,j), w);
        }

    }
    //G.printE();

    cout << G.Dijkstra(s, t);

    return 0;
}