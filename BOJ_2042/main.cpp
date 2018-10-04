#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<long long> arr;
vector<long long> tree;
vector<long long> answer;

long long initialize(vector<long long> &tree, int node, int ss, int se)
{
    if(ss == se) {
        return tree[node] = arr[ss];
    }
    int sm = (ss + se)/2;
    return tree[node] = initialize(tree, 2*node, ss, sm) + initialize(tree, 2*node + 1, sm + 1, se);
}

void update(vector<long long> &tree, int node, int ss, int se, int index, long long diff)
{
    if(ss > index || se < index) {
        return ;
    }
    tree[node] = tree[node] + diff;
    if(ss < se) {
        int sm = (ss + se)/2;
        update(tree, 2*node, ss, sm, index, diff);
        update(tree, 2*node + 1, sm+1, se, index, diff);
    }
}

long long getsum(int node, int ss, int se, int qs, int qe) // returns the sum of elements in the intersection of two segments [ss, se] and [qs, qe].
{
    if(se < qs || ss > qe) {
        return 0LL;
    }
    else if(qs <= ss && se <= qe) {
        return tree[node];
    }
    int sm = (ss + se)/2;
    return getsum(2*node, ss, sm, qs, qe) + getsum(2*node + 1, sm+1, se, qs, qe);

}

int main()
{
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    arr.resize(N);
    tree.resize(4*N);
    for(int i=0; i<N; i++) {
        scanf("%lld", &arr[i]);
    }
    initialize(tree, 1, 0, N-1);
    int a,b;
    long long c;
    for(int j=0; j<M+K; j++) {
        scanf("%d %d %lld", &a, &b, &c);
        if(a == 1) {
            long long diff = c - arr[b-1];
            arr[b-1] = c;
            update(tree, 1, 0, N-1, b-1, diff);
        }
        else if(a == 2) {
            long long result = getsum(1, 0, N-1, b-1, (int)c-1);
            answer.push_back(result);
        }
    }
    for(unsigned int j=0; j<answer.size(); j++) {
        printf("%lld\n", answer[j]);
    }
    return 0;
}
