#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

uint16_t prim(uint16_t n){
        if(n == 2) return 1;
        if(n < 2) return 0;
        if(n % 2 == 0) return 0;

        for(int d = 3; d * d <= n; d++)
                if(n % d == 0)
                        return 0;
        return 1;
}

void primeste_client(int s, struct sockaddr_in client) {
        uint16_t a;
        int l = sizeof(client);
        recvfrom(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr*) &client, &l);
        a = ntohs(a);

        printf("[From client] a = %hu\n", a);

        uint16_t rez = prim(a);
        a = htons(rez);
        sendto(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr*) &client, l);
        printf("[To client] send succesfully %hu\n", rez);
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

        while(1)
                primeste_client(s, client);

        close(s);
}
