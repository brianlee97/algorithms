#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> arr;
vector<int> tree;

int init(vector<int> &tree, int node, int ss, int se)
{
    if(ss == se) {
        return tree[node] = ss;
    }
    int mid = (ss + se)/2;
    int a = init(tree, 2*node, ss, mid);
    int b = init(tree, 2*node+1, mid+1, se);
    if(arr[a] > arr[b]) {
        return tree[node] = b;
    }
    else {
        return tree[node] = a;
    }
}

int rmq(int node, int ss, int se, int qs, int qe)
{
    int output;
    if(qs > se || qe < ss) {
        output = -1;
    }
    else if(qs <= ss && se <= qe) {
        output = tree[node];
    }
    else {
        int mid = (ss + se)/2;
        int a = rmq(2*node, ss, mid, qs, qe);
        int b = rmq(2*node + 1, mid+1, se, qs, qe);
        if(a == -1) {
            output = b;
        }
        else if(b == -1) {
            output = a;
        }
        else {
            if(arr[a] > arr[b]) {
                output = b;
            }
            else {
                output = a;
            }
        }
    }
    return output;
}

long long max_rectangle(vector<long long> &arr, int qs, int qe) {
    if(qs > qe) {
        return 0LL;
    }
    else if(qs == qe) {
        return arr[qs];
    }
    int n = arr.size();
    int pivot = rmq(1, 0, n-1, qs, qe);
    long long left_side = max_rectangle(arr, qs, pivot-1);
    long long right_side = max_rectangle(arr, pivot+1, qe);
    long long overall = (qe - qs + 1)*arr[pivot];
    long long maximum = max(left_side, max(right_side, overall));
    return maximum;
}

int main()
{
    int N;
    scanf("%d", &N);
    arr.resize(N);
    tree.resize(4*N);
    for(int i=0; i<N; i++) {
        scanf("%lld", &arr[i]);
    }
    init(tree, 1, 0, N-1);
    long long max_area = max_rectangle(arr, 0, N-1);
    printf("%lld", max_area);
    return 0;
}
