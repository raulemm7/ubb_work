//#include <cstdio>
#include <cstring>
//#include <cmath>
//#include <cstdlib>
#include <iostream>
//#include <climits>

using namespace std;

int main() {
    char mesaj[5005];
    cin >> mesaj;

    char key_1[2500];
    char key_2[2500];

    int min_lg;
    if(strlen(mesaj) % 3 != 0)
        min_lg = strlen(mesaj) / 3 + 1;
    else
        min_lg = strlen(mesaj) / 3;
    int max_ver = strlen(mesaj) / 2;
    for(int i = min_lg; i <= max_ver; i++) {
        int k = 0;
        for(int j = 0; j < i; j++) {
            key_1[j] = mesaj[k];
            k++;
        }
        key_1[i] = '\0';
        for(int j = 0; j < i; j++) {
            key_2[j] = mesaj[k];
            k++;
        }
        key_2[i] = '\0';

        if(strcmp(key_1, key_2) == 0) {
            char prefix[1900];
            int j = 0;
            while(k != strlen(mesaj)) {
                prefix[j] = mesaj[k];
                k++;
                j++;
            }
            prefix[j] = '\0';

            // lungime prefix = j
            if(strlen(prefix) < strlen(key_1)){
                bool ok = true;
                for(int vrf = 0; prefix[vrf] != '\0' and ok; vrf++) {
                    if(prefix[vrf] != key_1[vrf])
                        ok = false;
                }
                if(ok) {
                    cout << key_1;
                    return 0;
                }
            }
        }
    }
    cout << -1;
    return 0;
}
