#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STRING_SIZE 1024

void deservire_client(int c) {
        // primesc sirul
        uint16_t nr1;
        recv(c, &nr1, sizeof(uint16_t), MSG_WAITALL);
        nr1 = ntohs(nr1);

        uint16_t* numere1 = (uint16_t*)malloc(sizeof(uint16_t) * nr1);
        recv(c, numere1, sizeof(uint16_t) * nr1, MSG_WAITALL);

        uint16_t nr2;
        recv(c, &nr2, sizeof(uint16_t), MSG_WAITALL);
        nr2 = ntohs(nr2);

        uint16_t* numere2 = (uint16_t*)malloc(sizeof(uint16_t) * nr2);
        recv(c, numere2, sizeof(uint16_t) * nr2, MSG_WAITALL);

        uint16_t nr_nou = 0;
        uint16_t* numere = (uint16_t*)malloc(sizeof(uint16_t) * nr1);

        printf("[FROM CLIENT] Numere primite cu succes!\n");
        printf("[IN SERVER] Incepere prelucrare date...\n");

        for(int i = 0; i < nr1; i++) {
                bool ok = true;
                for(int j = 0; j < nr2; j++) {
                        if(numere1[i] == numere2[j]) {
                                ok = false;
                                j = nr2;
                        }
                }
                if(ok == true) {
                        numere[nr_nou] = htons(numere1[i]);
                        nr_nou++;
                }
        }
        nr_nou = htons(nr_nou);

        free(numere1);
        free(numere2);

        send(c, &nr_nou, sizeof(uint16_t), 0);
        send(c, numere, sizeof(uint16_t) * ntohs(nr_nou), 0);

        printf("[TO CLIENT] Numere trimise cu succes!\n");

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
                printf("[IN SERVER] S-a conectat un client.\n");
                if (fork() == 0) { // fiu
                        deservire_client(c);
                        printf("[IN SERVER] Client deconectat\n");
                        return 0;
                }

                // se executa doar in parinte pentru ca fiul se termina mai sus din cauza exit-ului
        }
}
