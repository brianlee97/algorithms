#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

char T[1000005] = {'\0'};
char P[1000005] = {'\0'};
int pi[1000001] = {0};
vector<int> pattern_index;

void findpi(char* P, int* pi, int N)
{
    pi[0] = 0;
    int j = 0;
    for(int i=1; i<N; i++) {
        while(j>0 && P[i] != P[j]) {
            j = pi[j-1];
        }
        if(P[i] == P[j]) {
            j++;
        }
        pi[i] = j;
    }
}

void KMP(char* T, char* P, int* pi, int M, int N)
{
    if(M < N) {
        return ;
    }
    int j = 0;
    for(int i=0; i<M; i++) {
        while(j>0 && T[i] != P[j]) {
            j = pi[j-1];
        }
        if(T[i] == P[j]) {
            j++;
        }
        if(j == N) {
            pattern_index.push_back(i-j+2);
            j = pi[j-1];
        }
    }
}

int main()
{
    cin.getline(T, 1000005);
    cin.clear();
    cin.getline(P, 1000005);
    cin.clear();
    int M = strlen(T);
    int N = strlen(P);
    findpi(P, pi, N);
    KMP(T, P, pi, M, N);
    int K = (int)pattern_index.size();
    cout << K << '\n';
    if(K > 0) {
        for(int l=0; l<K-1; l++) {
            cout << pattern_index[l] << '\n';
        }
        cout << pattern_index[K-1];
    }
    return 0;
}
