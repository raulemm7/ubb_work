#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 1024

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
        printf("[IN CLIENT] Sir de caractere: ");
        char* sir = (char*)malloc(sizeof(char) * STRING_SIZE);
        fgets(sir, STRING_SIZE, stdin);
        sir[strcspn(sir, "\n")] = '\0';  // pun terminator

        // trimit sirul
        send(c, sir, strlen(sir) + 1, 0);

        // citesc si trimit numerele i si l
        uint16_t i, l;
        printf("[IN CLIENT] Lungimea subsirului (l): ");
        scanf("%hu", &l);
        l = htons(l);

        printf("[IN CLIENT] Pozitia subsirului (i): ");
        scanf("%hu", &i);
        i = htons(i);

        send(c, &l, sizeof(uint16_t), 0);
        send(c, &i, sizeof(uint16_t), 0);

        free(sir);
        // primesc noul sir
        sir = (char*)malloc(sizeof(char) * (l + 1));
        recv(c, sir, sizeof(char) * (l + 1), 0);
        printf("[FROM SERVER] Subsirul este: %s\n", sir);

        close(c);
}
