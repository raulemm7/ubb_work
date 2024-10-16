#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

void deservire_client(int c) {
        uint16_t suma = 0;

        // primesc numarul de nr de la client
        uint16_t nr_numere;
        recv(c, &nr_numere, sizeof(nr_numere), MSG_WAITALL);
        nr_numere = ntohs(nr_numere);

        // parcurg numerele
        uint16_t* numere = (uint16_t*)malloc(nr_numere * sizeof(uint16_t));
        recv(c, numere, nr_numere * sizeof(uint16_t), MSG_WAITALL);

        for(int i = 0; i < nr_numere; i++) {
                suma += ntohs(numere[i]);
        }

        printf("[IN SERVER]Suma: %hu\n", suma);

        printf("Trimitere suma...\n");
        suma = htons(suma);
        send(c, &suma, sizeof(suma), 0);

        printf("Suma trimisa cu succes!\n");
        close(c);
        // sfarsitul deservirii clientului;
}

int main(int argc, char* argv[]) {
        if(argc < 2) {
                printf("Eroare! Mod utilizare: ./server port_number");
                return 1;
        }

        int s;
        struct sockaddr_in server, client;
        int c, l;

        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0) {
                printf("Eroare la crearea socketului server\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[1]));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la bind\n");
                return 1;
        }

        listen(s, 5);

        l = sizeof(client);
        memset(&client, 0, sizeof(client));

        while (1) {
                c = accept(s, (struct sockaddr *) &client, &l);
                printf("S-a conectat un client.\n");
                if (fork() == 0) { // fiu
                        deservire_client(c);
                        printf("Client deconectat de pe server!\n");
                        return 0;
                }

                // se executa doar in parinte pentru ca fiul se termina mai sus din cauza exit-ului
        }
}
