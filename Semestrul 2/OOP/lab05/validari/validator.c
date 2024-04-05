#include <string.h>

int validare_id(int id){
    if(id>0)
        return 1;
    return 0;
}

int validare_tip(char tip[]){
    if(strcmp(tip,"tractor")==0 || strcmp(tip,"laptop")==0 || strcmp(tip,"frigider")==0 || strcmp(tip,"televizor")==0 || strcmp(tip,"telefon")==0)
        return 1;
    return 0;
}

int validare_producator(char producator[]){
    if(strcmp(producator, "acer") == 0 || strcmp(producator, "fiat") == 0 || strcmp(producator, "apple") == 0 || strcmp(producator, "asus") == 0 || strcmp(producator, "hp") == 0)
        return 1;
    return 0;
}

int validare_pret(int pret){
    if(pret>=0)
        return 1;
    return 0;
}

int validare_cantitate(int cantitiate){
    if(cantitiate>0)
        return 1;
    return 0;
}
