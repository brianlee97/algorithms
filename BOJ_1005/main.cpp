#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int mintime[1001] = {0};
int construction_time[1001] = {0};

struct Graph{
    int V, E;
    vector<vector<int> > inward_list;

    Graph(int _V, int _E) {
        this->V = _V;
        this->E = _E;
    }

    void addEdge(int src, int dest) {
        inward_list[dest].push_back(src);
    }

    int minimumtime(int w) {
        if(inward_list[w].empty()) {
            return mintime[w] = construction_time[w];
        }
        else if(mintime[w] != -1) {
            return mintime[w];
        }
        vector<int> adjacent = inward_list[w];
        vector<int>::iterator itr = adjacent.begin();
        int min_time = -1;
        for(itr = adjacent.begin(); itr != adjacent.end(); ++itr) {
            min_time = max(min_time, minimumtime(*itr));
        }
        min_time = min_time + construction_time[w];
        return mintime[w] = min_time;
    }
};


int main()
{
    int T, N, K, W;
    vector<int> adj;
    int src, dest;
    scanf("%d", &T);
    int result[T] = {0};
    for(int i=0; i<T; i++) {
        memset(construction_time, 0, sizeof(construction_time));
        memset(mintime, -1, sizeof(mintime));
        scanf("%d %d", &N, &K);
        Graph graph(N, K);
        graph.inward_list.push_back(adj);
        for(int j=1; j<=N; j++) {
            scanf("%d", &construction_time[j]);
            graph.inward_list.push_back(adj);
        }
        for(int k=0; k<K; k++) {
            scanf("%d %d", &src, &dest);
            graph.addEdge(src, dest);
        }
        scanf("%d", &W);
        result[i] = graph.minimumtime(W);
    }

    for(int i=0; i<T; i++) {
        printf("%d\n", result[i]);
    }
    return 0;
}
