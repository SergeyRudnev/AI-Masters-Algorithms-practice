#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct vertex{
	vertex()= default;
};

class Graph{
	int n; // Number of vertices ≤ 10^5
public:
	vector<vertex> V;
	vector<vector<int>> adj_list;
	void add_edge(pair<int, int> p){
		adj_list[p.first-1].push_back(p.second-1);
        //adj_list[p.second-1].push_back(p.first-1);
	}
	Graph(int nn);
	void BFS();
	const vector<int> & neighbours(int v){return adj_list[v];}
};

void Graph::BFS(){
	queue<int> q;
	vector<bool> touched(n, false);
	for(int i = 0; i < n; ++i)
    {
		if(!touched[i])
        {
			q.push(i); touched[i] = true;
			while(!q.empty())
            {
				for(auto u : neighbours(q.front()))
                {
					if(!touched[u])
                    {
                        q.push(u);
                        touched[u] = true;
                    }
				}
				q.pop();
			}
		}
	}
}

Graph::Graph(int nn){
	n = nn;
	vector<vertex> VV(n, vertex());
	V=VV;
	adj_list = vector<vector<int>>(n, vector<int>());
}

struct DFS{
	Graph * G;
	int n; // Number of vertices == G->n
	int t; // Current time
	vector<int> d, f; // d — время открытия; f — время закрытия
					// d[u] > 0 — вершина открыта.

	DFS(Graph * GG){
		G = GG;
		n = G->V.size();
		t = 1; //!!! t == 0 -- вершина не открыта
		d = vector<int>(n, 0);
		f = vector<int>(n, 0);
	}
	void search(); // Full DFS;
	void search(int v); // DFS starting from v;
	void search_iter(); // DFS starting from v;
};

void DFS::search(){
	for(size_t u = 0; u < n; ++u){
		if(d[u] == 0){search(u);}
	}
}

void DFS::search(int v){// v — input; u — local
	d[v] = t++;
	for(auto u : G->neighbours(v)){
		if(d[u] == 0) search(u);
	}
	f[v] = t++;
}

void DFS::search_iter(){
	for(size_t v = 0; v < n; ++v){// v — input; u — local
		if(d[v] == 0){
			vector<pair<int, int> > st; // v, iu++
			st.emplace_back(v, 0);
			while(!st.empty()){
				auto [v, iu] = st.back();
				st.pop_back();
				if(d[v] == 0)
					d[v] = t++;
				bool call = false;
				auto & neigh = G->neighbours(v);
				for(; iu < neigh.size() && !call; ++iu){
					if(d[neigh[iu]] == 0){
						call = true;
						st.emplace_back(v, iu+1);
						st.emplace_back(neigh[iu], 0);
					}
				}
				if(!call) f[v] = t++;
			}
		 }
	}
}

int main (int argc, char const *argv[])
{
    std::ios::sync_with_stdio(false); std::cin.tie(0);
	int n, m, v, a, b, root;
	cin >> n;

	Graph G(n);

	for(int i = 1; i < n+1; ++i)
    {
        cin >> v;
        if (v != 0)
        {
            pair<int, int> p;
            p.first = v;
            p.second = i;
            G.add_edge(p);
        }
        else
            root = i;

	}
	DFS dfs(&G);
    dfs.search(root-1);
    cin >> m;

    for(int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        //cout << dfs.d[a-1] << " "<<dfs.d[b-1] << " "<< dfs.f[b-1] << " "<< dfs.f[a-1]<<"\n";
        if ((dfs.d[b-1] > dfs.d[a-1]) & (dfs.f[a-1] > dfs.f[b-1]))
            cout << 1 <<"\n";
        else
            cout << 0 <<"\n";
    }
	return 0;
}
