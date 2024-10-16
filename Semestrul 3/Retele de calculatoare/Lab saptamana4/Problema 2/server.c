#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

void deservire_client(int c) {
        uint16_t numar = 0;

        // primesc sirul de caractere
        char* sir_caractere = (char*)malloc(1024 * sizeof(char));
        // retin numarul de bytes
        int bytes_primiti = recv(c, sir_caractere, 1024 * sizeof(char), 0);
        // pun terminator
        printf("[IN SERVER] Numar bytes primiti: %d\n", bytes_primiti);
        sir_caractere[bytes_primiti] = '\0';
        printf("[IN SERVER] Sir primit: %s\n", sir_caractere);

        char* p = strtok(sir_caractere, " ");
        while(p) {
                numar++;
                p = strtok(NULL, " ");
        }

        printf("[IN SERVER] Nr de spatii goale: %hu\n", numar);

        printf("[TO CLIENT] Trimitere numar...\n");
        numar = htons(numar);
        send(c, &numar, sizeof(numar), 0);

        printf("[IN SERVER] Numar trimis cu succes!\n");
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
