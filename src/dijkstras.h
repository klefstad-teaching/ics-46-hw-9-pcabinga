#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

struct Edge {
    int src=0;
    int dst=0;
    int weight=0;
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    friend istream& operator>>(istream& in, Edge& e)
    {
        return in >> e.src >> e.dst >> e.weight;
    }

    friend ostream& operator<<(ostream& out, const Edge& e)
    {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};

struct Graph : public vector<vector<Edge>> {
    int numVertices=0;
};

inline istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices))
        throw runtime_error("Unable to find input file");
    G.resize(G.numVertices);
    for (Edge e; in >> e;)
        G[e.src].push_back(e);
    return in;
}

inline void file_to_graph(const string& filename, Graph& G) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    in >> G;
    in.close();
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
        int n = G.numVertices;
    vector<int> distances(n, INF);
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }

    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total){
    if (path.empty()) {
        cout << "No path found" << endl;
        return;
    }
    cout << "Shortest path (distance = " << total << "): ";
    for (int v : path) {
        cout << v << " ";
    }
    cout << endl;
}
