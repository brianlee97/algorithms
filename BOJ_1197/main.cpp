#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

// disjoint set data structure with union/find algorithms.
struct DisjointSet{
    vector<int> parent, level;

    // constructor
    DisjointSet(int n):parent(n), level(n,1){
        for(int i=0; i<n; i++){
            parent[i] = i;
        }
    }

    int find_set(int u){
        if(parent[u] == u)
            return u;
        return parent[u] = find_set(parent[u]);
    }

    void union_set(int u, int v){
        u = find_set(u);
        v = find_set(v);
        if(u == v){
            return ;
        }
        if(level[u] > level[v]){
            parent[v] = u;
        }
        else if(level[u] < level[v]){
            parent[u] = v;
        }
        else{
            parent[u] = v;
            level[v]++;
        }
    }
};

struct Edge{
    pair<int, int> edge;
    int weight;

    //constructor
    Edge(int src, int dest, int _weight){
        pair<int, int> _edge = make_pair(src, dest);
        this->edge = _edge;
        this->weight = _weight;
    }
};

struct EdgeCompare{
    bool operator()(Edge e, Edge f){
        return e.weight > f.weight;
    }
};

struct Graph{
    int V, E;
    priority_queue<Edge, vector<Edge>, EdgeCompare> edges;

    // constructor
    Graph(int _V, int _E){
        this->V = _V;
        this->E = _E;
    }

    void addEdge(int src, int dest, int weight){
        Edge e = Edge(src, dest, weight);
        edges.push(e);
    }

    int kruskalMST();
};

int Graph::kruskalMST()
{
    vector<Edge> mst;
    int mstweight = 0;
    DisjointSet ds(V);

    while(!edges.empty()){
        Edge e = edges.top();
        edges.pop();
        int u = ds.find_set(e.edge.first);
        int v = ds.find_set(e.edge.second);
        // examining whether a cycle exists by using disjoint set structure.
        if(u == v){
            continue;
        }
        else{
            mst.push_back(e);
            ds.union_set(u,v);
        }
    }
    vector<Edge>::iterator itr = mst.begin();
    for(itr = mst.begin(); itr != mst.end(); ++itr){
        mstweight += itr->weight;
    }
    return mstweight;
}

int main()
{
    int V, E;
    int src, dest, weight;
    int mstweight = 0;
    scanf("%d %d", &V, &E);
    Graph graph(V, E);
    for(int i=0; i<E; i++){
        scanf("%d %d %d", &src, &dest, &weight);
        graph.addEdge(src-1, dest-1, weight);
    }
    mstweight = graph.kruskalMST();
    printf("%d", mstweight);
    return 0;
}
