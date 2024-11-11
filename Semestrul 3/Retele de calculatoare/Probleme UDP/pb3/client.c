#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 256

void trimite_server(int c, struct sockaddr_in server) {
        char* sir = (char*)malloc(sizeof(char) * STRING_SIZE);
        fgets(sir, STRING_SIZE, stdin);
        sir[strcspn(sir, "\n")] = '\0';

        uint16_t lg = strlen(sir) + 1;
        lg = htons(lg);
        sendto(c, &lg, sizeof(uint16_t), 0, (struct sockaddr*) &server, sizeof(server));

        sendto(c, sir, ntohs(lg), 0, (struct sockaddr*) &server, sizeof(server));
        printf("send\n");

        int l = sizeof(server);
        uint16_t suma;
        recvfrom(c, &suma, sizeof(suma), MSG_WAITALL, (struct sockaddr*) &server, &l);
        suma = ntohs(suma);
        printf("[from server] numar spatii: %hu\n", suma);
}

int main(int argc, char* argv[]) {
        int c;
        struct sockaddr_in server;
        uint16_t a, b, suma, i, k;


        c = socket(AF_INET, SOCK_DGRAM, 0);
        if (c < 0) {
                printf("Eroare la crearea socketului client\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[1]));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        trimite_server(c, server);

        close(c);
}
