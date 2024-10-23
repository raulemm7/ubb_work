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
        char* sir = (char*)malloc(sizeof(char) * STRING_SIZE);
        int poz = 0;
        bool ok = true;
        while(ok) {
                char caracter;
                recv(c, &caracter, sizeof(char), 0);

                if(caracter == '\0') {
                        ok = false;
                }

                sir[poz] = caracter;
                poz++;
        }

        // primesc lungimea si indexul
        uint16_t lung, index;
        recv(c, &lung, sizeof(uint16_t), 0);
        lung = ntohs(lung);

        recv(c, &index, sizeof(uint16_t), 0);
        index = ntohs(index);

        printf("[FROM CLIENT] Date primiite cu succes!\n");

        char* sir_nou = (char*)malloc(sizeof(char) * (lung + 1));
        int i;
        for(i = 0; i < lung && index + i < strlen(sir); i++) {
                sir_nou[i] = sir[index + i];
        }
        sir_nou[i] - '\0';

        printf("[TO CLIENT] TRIMITERE SIR...\n");
        send(c, sir_nou, strlen(sir_nou) + 1, 0);

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
