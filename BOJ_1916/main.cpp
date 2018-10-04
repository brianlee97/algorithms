#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

struct Edge{
    int dest;
    int weight;

    Edge(int _dest, int _weight){
        this->dest = _dest;
        this->weight = _weight;
    }
};

struct Graph{
    int V, E;
    vector<vector<Edge> > adjlist;
    vector<int> distance;

    Graph(int V, int E){
        this->V = V;
        this->E = E;
        vector<vector<Edge> > adj_list(V);
        this->adjlist = adj_list;
        vector<int> _distance(V, 1000000000);
        this->distance = _distance;
    }

    void addEdge(int src, int dest, int weight){
        Edge e(dest, weight);
        adjlist[src].push_back(e);
    }

    void dijkstra(int source);
};

struct Vertex{
    int node;
    int mindistance;

    Vertex(int _node, int _mindistance){
        this->node = _node;
        this->mindistance = _mindistance;
    }
};

struct VertexCompare{
    bool operator() (Vertex u, Vertex v){
        return u.mindistance > v.mindistance;
    }
};

void Graph::dijkstra(int source)
{
    distance[source] = 0;
    priority_queue<Vertex, vector<Vertex>, VertexCompare> pq;
    bool visited[V] = {false}; // it indicates that whether the update of minimum distance of a node is already done.
    Vertex v(source, distance[source]);
    pq.push(v);
    while(!pq.empty()){
        Vertex current = pq.top(); // get the node of minimum distance from the source.
        pq.pop();
        if(current.mindistance > distance[current.node]){
            continue; // the case of the object "Vertex" has an "old information" of minimum distance from the source.
        }
        visited[current.node] = true;
        vector<Edge> adjacent_nodes = adjlist[current.node];
        vector<Edge>::iterator itr = adjacent_nodes.begin();
        for(itr = adjacent_nodes.begin(); itr != adjacent_nodes.end(); ++itr){
            if(!visited[itr->dest] && distance[current.node] + itr->weight < distance[itr->dest]){
                distance[itr->dest] = distance[current.node] + itr->weight;
                Vertex u(itr->dest, distance[itr->dest]);
                pq.push(u);
            }
        }
    }
}

int main()
{
    int V, E, A, B;
    int src, dest, weight;
    scanf("%d", &V);
    scanf("%d", &E);
    Graph graph(V, E);
    for(int i=0; i<E; i++){
        scanf("%d %d %d", &src, &dest, &weight);
        graph.addEdge(src-1, dest-1, weight);
    }
    scanf("%d %d", &A, &B);
    A--;
    B--;
    graph.dijkstra(A);
    printf("%d", graph.distance[B]);
    return 0;
}
