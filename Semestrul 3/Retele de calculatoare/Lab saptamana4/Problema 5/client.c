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

        // citesc numarul de la tastatura
        uint16_t numar;
        printf("[IN CLIENT] Numar: ");
        scanf("%hu", &numar);

        // trimit numaruk
        numar = htons(numar);
        send(c, &numar, sizeof(numar), 0);

        // primesc sirul cu divizorii
        // primesc mai intai numarul de divizori
        uint16_t nr_div;
        recv(c, &nr_div, sizeof(nr_div), MSG_WAITALL);
        nr_div = ntohs(nr_div);

        // primesc divizorii
        uint16_t* divs = (uint16_t*)malloc(sizeof(uint16_t) * nr_div);
        recv(c, divs, sizeof(uint16_t) * nr_div, 0);

        printf("[FROM SERVER] Sirul cu divizori: ");
        for(uint16_t i = 0; i < nr_div; i++) {
                printf("%hu, ", ntohs(divs[i]));
        }
        printf("\n");

        close(c);
}
