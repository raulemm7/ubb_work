//
// Created by raulo on 5/23/2024.
//

#include "repository.h"
#include <fstream>
#include <cstring>

vector<Rochie> &Repository::getListaRochii() {
    return this->lista_rochii;
}

string Repository::set_disponibilitate(int cod) {
    for(auto& item:this->lista_rochii) {
        if(item.getCod() == cod){
            if(item.isDisponibilitate()) {
                item.setDisponibilitate();
                return "Rochie inchiriata cu succes!";
            }
            else
                return "Rochia este deja inchiriata!";
        }
    }
    return "Nu s-a gasit rochia!";
}

void Repository::load_from_file() {
    int cod, pret;
    string nume, marime;
    bool disponibilitate;

    // cod,nume,marime,pret,disponibilitate
    std::ifstream fin(this->nume_fisier);

    char* linie_buffer = (char*)malloc(sizeof(char) * 128);
    while(fin.getline(linie_buffer, 128)) {
        int it = 0;
        char *p = strtok(linie_buffer, ",");
        while(p) {
            if(it == 0) {
                // cod
                cod = stoi(p);
            }
            if(it == 1) {
                // nume
                nume = p;
            }
            if(it == 2) {
                // marime
                marime = p;
            }
            if(it == 3) {
                // pret
                pret = stoi(p);
            }
            if(it == 4) {
                // disponibilitate
                if(!strcmp(p, "true")) {
                    disponibilitate = true;
                }
                else
                    disponibilitate = false;
            }

            it++;
            p = strtok(NULL, ",");
        }

        Rochie r{cod, nume, marime, pret, disponibilitate};
        this->lista_rochii.push_back(r);
    }

    fin.close();
}

void Repository::save_to_file() {
    this->clear_file();

    std::ofstream fout(this->nume_fisier);

    auto vec = this->getListaRochii();
    for(auto const& item : vec) {
        string info;
        info += std::to_string(item.getCod()) + ",";
        info += item.getDenumire() + ",";
        info += item.getMarime() + ",";
        info += std::to_string(item.getPret()) + ",";

        if(item.isDisponibilitate())
            info += "true\n";
        else
            info += "false\n";

        fout << info;
    }

    fout.close();
}

void Repository::clear_file() {
    std::ofstream fout;
    fout.open(this->nume_fisier, std::ofstream::out | std::ofstream::trunc);
    fout.close();
}
