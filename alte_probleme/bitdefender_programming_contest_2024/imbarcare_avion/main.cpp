/*#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>*/
#include <iostream>
//#include <climits>

using namespace std;

int n;
int v[2100];

int s(int st, int dr, int suma) {
    if(st < dr) {
        if(v[st] + v[st + 1] == suma)
            return 2 + s(st + 2, dr, suma);
        else if(v[st] + v[dr] == suma) {
            return 2 + s(st + 1, dr - 1, suma);
        }
        else if(v[dr - 1] + v[dr] == suma) {
            return 2 + s(st, dr - 2, suma);
        }
    }
    return 0;
}

int alg() {
    int k1 = 2 + s(3, n, v[1] + v[2]);
    int k2 = 2 + s(2, n - 1, v[1] + v[n]);
    int k3 = 2 + s(1, n - 2, v[n-1] + v[n]);

    int m = max(k1, k2);
    return max(k3, m);
}

int main() {
    int i;
    cin >> n;
    for(i = 1; i <= n; i++) {
        cin >> v[i];
    }
    cout << alg();
    return 0;
}
