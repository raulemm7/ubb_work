#include <stdio.h>

/*
 * functie ce afiseaza meniul aplicatiei
 * preconditii: adevarat
 * postconditii: adevarat
 */
void menu() {
    printf("1. Calculeaza primele k zecimale ale fractiei subunitare n/m;\n");
    printf("2. Afiseaza descompunerea in factori primi a unui numar;\n");
    printf("3. Iesire din aplicatie;\n");
}

/*
 * functie citeste un numar ce reprezinta o comanda pentru a efectua o
 * instructiune din meniu
 * preconditii: un numar NR_MAX natural, reprezentand numarul maxim de c
 *              comenzi
 * postconditii: un numar natural reprezentand o comanda corecta
 */
int citire_comanda(int NR_MAX) {
    while(1) {
        printf("Citeste o comanda: ");
        int comanda;
        scanf("%d", &comanda);
        if(comanda > 0 && comanda <= NR_MAX)
            return comanda;
        printf("Citeste corect o comanda!\n");
    }
}

/*
 * functie ce citeste corect numitorul unei fractii tinand
 * cont de numaratorul acesteia
 * preconditii: un numar natural reprezentand numaratorul unei fractii
 * postconditii: un numar natural reprezentand numitorul unei fractii
 */
int citeste_corect_m(int n) {
    while(1) {
        int m;
        printf("%s", "Citeste m: ");
        scanf("%d", &m);
        if(n < m)
            return m;
        printf("%s", "Atentie! Fractia n/m trebuie sa fie subunitara!\n");
    }
}

/* pb 4
 * functie ce calculeaza si afiseaza pe ercan primele k zecimale ale
 * fractiei subunitare n/m
 * preconditii: k, n si m numere naturale
 * postconditii: adevarat
 */
void calculeaza_zecimale(int k, int n, int m) {
    if(k) {
        int cat = 0;

        n *= 10;
        while(n >= m) {
            n -= m;
            cat += 1;
        }

        if(!n) {
            // daca n == 0 am o fractie zecimala finita
            // afisez cifra calculata, iar pentru restul zecimalelor
            // cerute afisez zerouri
            printf("%d", cat);
            k -= 1;
            while(k){
                printf("%d", 0);
                k--;
            }
        }
        else {
            printf("%d", cat);
            calculeaza_zecimale(k - 1, n, m);
        }
    }
}

/* pb13
 * functie ce afiseaza descompunerea in factori primi a unui numar
 * preconditii: numar sa fie un nr natural nenul
 * postconditii: adevarat
 */
void descompunere_factori_primi(int numar) {
    int d = 2;  // factor prim
    int p;      // puterea acestuia
    int ok = 0; // un bool pentru formatarea afisarii

    while(numar > 1) {
        // numaram de cate ori se imparte d la n
        // aceasta va fi puterea lui d in descompunere
        p = 0;
        while(numar % d == 0) {
            p++;
            numar /= d;
        }

        // daca p > 0 afisez factorul prim si puterea lui
        if(p) {
            if(!ok) {
                printf("%d^%d", d, p);
                ok = 1;
            }
            else {
                printf(" + %d^%d", d, p);
            }
        }

        d++;
        // daca d * d > numar si numar > 1, decidem ca numar este prim
        // si este factor in descompunerea valorii initiale a lui numar
        if(numar > 1 && d * d > numar)
            d = numar;
    }
    printf("\n");
}

int main() {
    while(1) {
        menu();
        int command = citire_comanda(3);
        if(command == 1) {
            // pb 4
            int n, m, k;

            printf("Citeste n: ");
            scanf("%d", &n);

            m = citeste_corect_m(n);

            printf("Citeste numarul de zecimale pe care vrei sa le afisezi: ");
            scanf("%d", &k);

            printf("0.");
            calculeaza_zecimale(k, n, m);
            printf("\n");
        }
        else if(command == 2) {
            // pb 13
            int n;

            printf("Citeste numarul pentru care se face descompunerea in factori primi: ");
            scanf("%d", &n);
            descompunere_factori_primi(n);
        }
        else
            return 0;
    }
}

/*
 * lab: pb13
 * lab2 : pb7
 */
