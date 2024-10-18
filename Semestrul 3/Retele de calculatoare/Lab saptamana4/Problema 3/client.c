#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

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

        // citesc sirul de caractere
        char* sir_char = (char*)malloc(sizeof(char) * 1024);
        printf("[IN CLIENT] Sir de caractere: ");
        fgets(sir_char, 1024, stdin);
        sir_char[strcspn(sir_char, "\n")] = '\0';  // Înlocuiesc '\n' cu terminatorul nul '\0'

        // verific daca e ok ce citesc
        printf("[IN CLIENT] Numar bytes cititi: %d\n", strlen(sir_char) + 1);

        // trimit sirul de caractere
        int k = send(c, sir_char, strlen(sir_char) + 1, 0);   // trimit cu '\0'
        printf("[IN CLIENT] Numar bytes trimisi: %d\n", k);

        // primesc noul sir
        char* sir_nou = (char*)malloc(sizeof(char) * k);
        recv(c, sir_nou, sizeof(char) * k, 0);
        printf("[FROM SERVER] Sirul nou: %s\n", sir_nou);

        close(c);
}
