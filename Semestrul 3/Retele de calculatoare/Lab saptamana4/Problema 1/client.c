#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

struct infoNumere{
        uint16_t nr_numere;
        uint16_t* numere;
};

struct infoNumere numereFromChars(char* numere){
        uint16_t numar_numere = 0;
        uint16_t* numere_pars = (uint16_t*)malloc(sizeof(uint16_t) * 205);

        char* p = strtok(numere, " ");
        while(p) {
                numere_pars[numar_numere] = htons(atoi(p));
                numar_numere++;

                p = strtok(NULL, " ");
        }

        struct infoNumere s;
        s.nr_numere = htons(numar_numere);
        s.numere = numere_pars;

        return s;
}

int main(int argc, char* argv[]) {
        if(argc < 2) {
                printf("Eroare! Mod utilizare: ./client port_number");
                return 1;
        }

        int c;
        struct sockaddr_in server;

        c = socket(AF_INET, SOCK_STREAM, 0);
        if (c < 0) {
                printf("Eroare la crearea socketului client\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[1]));           // port dat in linia de comanda
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");  // local host

        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server\n");
        return 1;
        }

        // citesc numerele
        char* numere_char = (char*)malloc(sizeof(char) * 1024);
        printf("Dati numere sep prin spatiu pt suma: ");
        fgets(numere_char, 1024, stdin);

        // parsez informatiile citite, le pun intr-un struct cu info
        struct infoNumere st = numereFromChars(numere_char);

        // trimit nr de numere
        send(c, &st.nr_numere, sizeof(st.nr_numere), 0);

        // trimit array -ul
        send(c, st.numere, st.nr_numere * sizeof(uint16_t), 0);
        printf("Numere trimise cu succes catre server!\n");

        // primesc suma de numere
        uint16_t suma;
        recv(c, &suma, sizeof(suma), 0);
        suma = ntohs(suma);
        printf("Suma este %hu\n", suma);

        close(c);
}
