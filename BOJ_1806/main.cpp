#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> sequence;

int main()
{
    int N, S, entry;
    scanf("%d %d", &N, &S);
    for(int i=0; i<N; i++) {
        scanf("%d", &entry);
        sequence.push_back(entry);
    }
    int minlength = 200000;
    int sum = 0;
    int endpointer = 0;
    for(int i=0; i<N; i++) {
        while(sum < S && endpointer < N) {
            sum = sum + sequence[endpointer];
            endpointer++;
        }
        if(endpointer == N && sum < S) {
            break;
        }
        minlength = min(minlength, endpointer - i);
        sum = sum - sequence[i];
    }
    if(minlength == 200000) {
        printf("%d", 0);
    }
    else {
        printf("%d", minlength);
    }
    return 0;
}
