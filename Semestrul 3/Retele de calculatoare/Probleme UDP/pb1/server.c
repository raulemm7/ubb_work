#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

void primeste_client(int s, struct sockaddr_in client) {
        uint16_t a, b;
        int l = sizeof(client);
        recvfrom(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr*) &client, &l);
        a = ntohs(a);

        recvfrom(s, &b, sizeof(b), MSG_WAITALL, (struct sockaddr*) &client, &l);
        b = ntohs(b);

        printf("[From client] a = %hu, b = %hu\n", a, b);

        a += b;
        a = htons(a);
        sendto(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr*) &client, l);
        printf("[To client] send succesfully\n");
}


int main(int argc, char* argv[]) {
        int s;
        struct sockaddr_in server, client;
        int c, l, i;
        uint16_t k, old = 0;

        s = socket(AF_INET, SOCK_DGRAM, 0);
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

        l = sizeof(client);
        memset(&client, 0, sizeof(client));

        primeste_client(s, client);

        close(s);
}
