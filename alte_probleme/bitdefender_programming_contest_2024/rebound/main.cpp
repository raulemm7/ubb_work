//#include <cstdio>
#include <cstring>
//#include <cmath>
//#include <cstdlib>
#include <iostream>
//#include <climits>

using namespace std;

/**
  * MARE DISCLAIMER
  * SOLUTIA NU A FOST ACCEPTATA DEOARECE EA NU SE INCADREAZA IN LIMITA DE TIMP, CHIAR DACA ACEASTA DA UN RASPUNS CORECT
  */

int nr;
int nr_oglinzi = 0;

struct oglinda {
    int x;
    int y1, y2;
}oglinzi[200005];

int min_x, max_x;
int min_y, max_y;

void sortare_oglinzi() {
    for(int i = 1; i < nr_oglinzi; i++) {
        for(int j = i + 1; j <= nr_oglinzi; j++) {
            if(oglinzi[i].x > oglinzi[j].x)
                swap(oglinzi[i], oglinzi[j]);
            else if(oglinzi[i].x == oglinzi[j].x) {
                if(oglinzi[j].y1 > oglinzi[i].y2)
                    swap(oglinzi[i], oglinzi[j]);
            }
        }
    }
}

int calculate_oglinzi(int x, int y) {
    int nr_ = 0;

    int delta_x = +1;
    while(x <= max_x and x >= min_x and y <= max_y and y >= min_y) {
        x += delta_x;
        y += 1;

        for(int i = 1; i <= nr_oglinzi; i++) {
            if(x == oglinzi[i].x) {
                if(y <= oglinzi[i].y2 and y >= oglinzi[i].y1) {
                    nr_++;
                    i += nr_oglinzi;
                    delta_x *= -1;
                }
            }
        }
    }

    return nr_;
}

int main() {
    int x;
    cin >> nr;
    for(int i = 1; i <= nr; i++) {
        cin >> x;
        if(x == 1) {
            nr_oglinzi++;
            cin >> oglinzi[nr_oglinzi].x >> oglinzi[nr_oglinzi].y1 >> oglinzi[nr_oglinzi].y2;

            if(i == 1) {
                max_x = min_x = oglinzi[nr_oglinzi].x;
                min_y = oglinzi[nr_oglinzi].y1;
                max_y = oglinzi[nr_oglinzi].y2;
            }

            if(oglinzi[nr_oglinzi].x < min_x)
                min_x = oglinzi[nr_oglinzi].x;
            if(oglinzi[nr_oglinzi].x > max_x)
                max_x = oglinzi[nr_oglinzi].x;
            if(oglinzi[nr_oglinzi].y1 < min_y)
                min_y = oglinzi[nr_oglinzi].y1;
            if(oglinzi[nr_oglinzi].y2 > max_y)
                max_y = oglinzi[nr_oglinzi].y2;
        }
        else {
            sortare_oglinzi();
            int y;
            cin >> x >> y;
            cout << calculate_oglinzi(x, y) << "\n";
        }
    }
}
