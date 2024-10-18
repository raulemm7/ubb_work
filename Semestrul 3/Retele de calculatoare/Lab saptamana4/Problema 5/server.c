#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

void deservire_client(int c) {
        // primesc numarul
        uint16_t numar;
        recv(c, &numar, sizeof(uint16_t), 0);
        numar = ntohs(numar);
        printf("[FROM CLIENT] Numar primit: %hu\n", numar);

        // fac divizorii
        uint16_t nr_div = 0;
        uint16_t* divs = (uint16_t*)malloc(sizeof(uint16_t) * 1024);

        // calculez divizorii
        // fac cea mai nesimtita rezolvare
        for(int i = 1; i <= numar; i++) {
                if(!(numar % i)) {
                        divs[nr_div] = htons(i);
                        nr_div++;
                }
        }

        // trimit mai intai numarul de divizori
        nr_div = htons(nr_div);
        send(c, &nr_div, sizeof(nr_div), 0);

        // trimit acum divizorii
        send(c, divs, sizeof(uint16_t) * nr_div, 0);

        printf("[TO CLIENT] Si cu divizori calculat si trimit cu succes!\n");
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
