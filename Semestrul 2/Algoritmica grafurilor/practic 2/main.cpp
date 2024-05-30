#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Nod {
    char c;
    int frecventa;
    Nod* stanga;
    Nod* dreapta;
    Nod(char caracter, int frecv) : c(caracter), frecventa(frecv), stanga(nullptr), dreapta(nullptr) {}
};

struct Comparator {
    bool operator()(Nod* stanga, Nod* dreapta) {
        return stanga->frecventa > dreapta->frecventa;
    }
};

Nod* construesteArboreHuffman(const string& mesaj) {
    // calculez frecventa fiecarei litere
    vector<int> frecvente(256, 0);
    for (char c : mesaj) {
        frecvente[c]++;
    }

    // creez nodurile cu litere si frecventa respectiva, le pun intr un
    // priority queue
    priority_queue<Nod*, vector<Nod*>, Comparator> pq;
    for (int i = 0; i < 256; ++i) {
        if (frecvente[i] > 0) {
            pq.push(new Nod(i, frecvente[i]));
        }
    }

    // construiesc arborele
    while (pq.size() != 1) {
        Nod* stanga = pq.top(); pq.pop();
        Nod* dreapta = pq.top(); pq.pop();
        Nod* nou = new Nod('\0', stanga->frecventa + dreapta->frecventa);
        nou->stanga = stanga;
        nou->dreapta = dreapta;
        pq.push(nou);
    }

    return pq.top();
}

// pentru fiecare litera generez codul din arborele huffman si le adaug in vectorul de perechi
void generareCoduri(Nod* radacina, const string& cod, vector<pair<char, string>>& coduriHuffman) {
    if (!radacina) return;
    if (!radacina->stanga && !radacina->dreapta) {
        coduriHuffman.push_back({radacina->c, cod});
    }
    generareCoduri(radacina->stanga, cod + "0", coduriHuffman);
    generareCoduri(radacina->dreapta, cod + "1", coduriHuffman);
}

string comprima(const string& mesaj, const vector<pair<char, string>>& coduriHuffman) {
    // pentru fiecare litera din mesaj, iau codul asociat literei si il adaug mesajului final
    string mesaj_comprimat;
    for (char c : mesaj) {
        for (const auto& pereche : coduriHuffman) {
            if (pereche.first == c) {
                mesaj_comprimat += pereche.second;
                break;
            }
        }
    }
    return mesaj_comprimat;
}

string decomprima(const string& mesaj_comprimat, Nod* radacina) {
    // pentru fiecare bit din mesaj, parcurg arborele in functie de valoarea lui pentru
    // a ajunge la litera care se afla pe o frunza
    string mesaj_decomprimat;
    Nod* curent = radacina;
    for (char bit : mesaj_comprimat) {
        if (bit == '0') curent = curent->stanga;
        else curent = curent->dreapta;
        // daca e frunza, ma aflu pe o litera
        if (!curent->stanga && !curent->dreapta) {
            mesaj_decomprimat += curent->c;
            curent = radacina;
        }
    }
    return mesaj_decomprimat;
}

int main() {
    string mesaj = "Treeaaassuureee";
    vector<pair<char, string>> coduriHuffman;
    Nod* radacina = construesteArboreHuffman(mesaj);
    generareCoduri(radacina, "", coduriHuffman);

    string mesaj_comprimat = comprima(mesaj, coduriHuffman);
    cout << "Mesaj comprimat: " << mesaj_comprimat << endl;

    string mesaj_decomprimat = decomprima(mesaj_comprimat, radacina);
    cout << "Mesaj decomprimat: " << mesaj_decomprimat << endl;

    return 0;
}
