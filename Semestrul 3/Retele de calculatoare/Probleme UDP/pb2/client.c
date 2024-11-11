#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

void trimite_server(int c, struct sockaddr_in server) {
        uint16_t a, b, suma;
        printf("Numarul a: ");
        scanf("%hu", &a);
        a = htons(a);

        sendto(c, &a, sizeof(a), 0, (struct sockaddr*) &server, sizeof(server));

        int l = sizeof(server);
        recvfrom(c, &suma, sizeof(suma), MSG_WAITALL, (struct sockaddr*) &server, &l);
        suma = ntohs(suma);
        a = ntohs(a);
        if(suma)
                printf("%hu este prim\n", a);
        else
                printf("%hu nu este prim\n", a);
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
