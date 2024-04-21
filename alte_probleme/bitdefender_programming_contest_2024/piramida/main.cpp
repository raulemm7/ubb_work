/*#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>*/
#include <iostream>
//#include <climits>

using namespace std;

/**
  *  SOLUTIE CORECTA, DAR LENTA
  */

int main() {
    long long nr_rotatii;
    cin >> nr_rotatii;
    if(nr_rotatii <= 4) {
        cout << 1;
        return 0;
    }
    long long a = 1, b = 1, c = 1, d = 1;
    long long s;
    for(int i = 4 + 1; i <= nr_rotatii; i++) {
        s = (a + d) % 999999937;
        a = b;
        b = c;
        c = d;
        d = s;
    }
    cout << s % 999999937;
    return 0;
}
