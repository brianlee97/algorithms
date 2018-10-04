#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

#define MAX 20000000

using namespace std;

int W[17][17] = {0};
int dp[17][(1<<17)];
int N;

int tsp(int current, int visited)
{
    if(dp[current][visited] != -1) {
        return dp[current][visited];
    }
    if(visited == ((1<<N)-1)) {
        if(W[current][1] > 0) {
            return W[current][1];
        }
        else {
            return MAX;
        }
    }
    int result = MAX;
    for(int next = 1; next <= N; next++) {
        if(W[current][next] > 0 && !(visited & (1<<(next-1)))) {
            result = min(result, W[current][next] + tsp(next, visited | (1<<(next-1))));
        }
    }
    return dp[current][visited] = result;
}


int main()
{
    scanf("%d", &N);
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            scanf("%d", &W[i][j]);
        }
    }
    memset(dp, -1, sizeof(dp));
    int answer = tsp(1, 1);
    printf("%d", answer);
    return 0;
}
