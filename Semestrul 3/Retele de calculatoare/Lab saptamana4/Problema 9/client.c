#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 1024

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
        server.sin_port = htons(atoi(argv[1]));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la conectarea la server\n");
                return 1;
        }

        // citesc primul sir de numere
        char* sir_caractere = (char*)malloc(sizeof(char) * STRING_SIZE);
        printf("Primul sir: ");
        fgets(sir_caractere, STRING_SIZE, stdin);

        // parsez informatiile citite si le retin intr un struct
        struct infoNumere info1 = numereFromChars(sir_caractere);

        // citesc si al doilea sir
        memset(sir_caractere, 0, STRING_SIZE);
        printf("Al doilea sir: ");
        fgets(sir_caractere, STRING_SIZE, stdin);

        // parsez info
        struct infoNumere info2 = numereFromChars(sir_caractere);
        free(sir_caractere);

        // informatiile sunt deja transformate pentru network, trebuie doar sa le trimti
        // trimit primul sir
        send(c, &info1.nr_numere, sizeof(uint16_t), 0);
        send(c, info1.numere, sizeof(uint16_t) * ntohs(info1.nr_numere), 0);

        // al doilea
        send(c, &info2.nr_numere, sizeof(uint16_t), 0);
        send(c, info2.numere, sizeof(uint16_t) * ntohs(info2.nr_numere), 0);

        printf("[TO SERVER] Numere trimise cu succes!\n");

        // primesc sirul de numere
        uint16_t nr;
        recv(c, &nr, sizeof(uint16_t), 0);
        nr = ntohs(nr);

        if(nr == 0) {
                printf("[FROM SERVER] Nu exista numere in primul sir care sa nu fie si in al doilea!\n");
                close(c);
                return 0;
        }

        uint16_t* numere = (uint16_t*)malloc(sizeof(uint16_t) * nr);
        recv(c, numere, sizeof(uint16_t) * nr, MSG_WAITALL);

        printf("[FROM SERVER] Numere din primul sir care nu sunt si in al doilea: ");
        for(int i = 0; i < nr; i++) {
                printf("%hu, ", numere[i]);
        }
        printf("\n");
        close(c);
}
