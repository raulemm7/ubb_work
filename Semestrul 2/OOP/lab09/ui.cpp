//
// Created by raulo on 4/2/2024.
//

#include "ui.h"
#include "domain.h"
#include <numeric>
#include "validators.h"

const void ui_operations::show_menu() {
    std::cout << "1. Adauga medicament\n";
    std::cout << "2. Sterge medicament\n";
    std::cout << "3. Modifica medicament\n";
    std::cout << "4. Afisare medicamente\n";
    std::cout << "5. Cautare medicament\n";
    std::cout << "6. Filtrare medicamente\n";
    std::cout << "7. Sortare medicamente\n";
    std::cout << "8. Creeaza reteta\n";
    std::cout << "9. Genereaza raport medicamente\n";
    std::cout << "10. Undo\n";
    std::cout << "11. Iesire din aplicatie\n";
    std::cout << "0. Adaugare rapida (adauga 10 medicamente)\n";
}

const void ui_operations::show_menu_for_prescription() {
    std::cout << "1. Adaugare medicament la reteta\n";
    std::cout << "2. Sterge toate medicamentele de pe reteta\n";
    std::cout << "3. Genereaza automat reteta\n";
    std::cout << "4. Exporta reteta\n";
    std::cout << "5. Inapoi\n";
}

const void ui_operations::show_message(const std::string& msg) {
    std::cout << msg << '\n';
}

const void ui_operations::show_menu_for_filter() const {
    std::cout << "1. Filtrare dupa pret\n";
    std::cout << "2. Filtrare dupa substanta_activa\n";
}

const void ui_operations::show_menu_for_sort() const {
    std::cout << "1. Sortare dupa denumire\n";
    std::cout << "2. Sortare dupa producator\n";
    std::cout << "3. Sortare dupa substanta activa + pret\n";
}

const void ui_operations::print_one_med(const Medicament &medicament) const {
    std::cout << medicament.get_id() << "    |    " << medicament.get_denumire() << "    |    "
              << medicament.get_pret() << "    |    " << medicament.get_producator() << "    |    "
              << medicament.get_subst_activa() << "\n";
}

const void ui_operations::print_meds(MedicamenteRepo& storage, const string& header) const{
    std::cout << header;
    for(int i = 0; i < storage.get_last_id(); i++) {
        const Medicament& med = storage.get_med(i);
        print_one_med(med);
    }
}

const int ui_operations::read_command(const int &MAX_COMMAND) {
    while(true) {
        int citire_comanda;
        std::cout << "Introdu o comanda: ";
        std::cin >> citire_comanda;

        if(citire_comanda >= 0 and citire_comanda <= MAX_COMMAND)
            return citire_comanda;

        std::cout << "Introdu o comanda corecta!\n";
    }
}

string ui_operations::read_name_file() {
    while(true) {
        string file_name;
        std::cout << "Introdu numele fisierului in care doresti sa salvezi informatiile: ";
        std::cin >> file_name;

        if(Validator::validare_nume_fisier(file_name))
            return file_name;

        std::cout << "Introdu un nume corect de fisier (trebuie sa contina extensia .html)!!\n";
    }
}

const string ui_operations::citire_string(const string& msg) {
    std::cout << msg;
    string de_citit;
    std::cin >> de_citit;
    return de_citit;
}

const int ui_operations::citire_pret(const string &msg1, const string &msg2) {
    while(true) {
        int pret;
        std::cout << msg1;

        while(!(std::cin >> pret)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Valoarea introdusa nu este un numar!\n";
            std::cout << msg1;
        }

        if(pret > 5)
            return pret;

        std::cout << msg2 << '\n';
    }
}

const int ui_operations::read_id(const int &MAX_ID, const string& msg_out, const string& msg_err) {
    while(true) {
        int id_ales;
        std::cout << msg_out;

        while(!(std::cin >> id_ales)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Valoarea introdusa nu este un numar!\n";
            std::cout << msg_out;
        }

        if(0 <= id_ales and id_ales <= MAX_ID)
            return id_ales;

        std::cout << msg_err << '\n';
    }
}

const int ui_operations::read_id_with_string(MedicamenteRepo &storage, const string &msg_out, const string &msg_err) {
    while(true) {
        std::cout << msg_out;

        string string_citit;
        std::cin >> string_citit;

        int id_ales = Validator::valideaza_med_dupa_denumire(storage, string_citit);
        if(id_ales > -1)
            return id_ales;

        std::cout << msg_err;
    }
}

const Medicament ui_operations::citire_medicament(const int &id) {
    string denumire = citire_string("Introdu denumirea noului medicament: ");
    int pret = citire_pret("Introdu pretul noului medicament: ", "Introdu un pret corect!");
    string producator = citire_string("Introdu producatorul noului medicament: ");
    string subst_activa = citire_string("Introdu substanta activa a noului medicament: ");

    Medicament med(id, denumire, pret, producator, subst_activa);
    return med;
}

const char ui_operations::citire_operator_filtrare(const string& msg, const string& msg_err) {
    char operatori[] = {'>', '=', '<'};
    while(true) {
        std::cout << msg;

        char op;
        std::cin >> op;

        for(char i : operatori) {
            if(i == op)
                return op;
        }

        std::cout << msg_err << '\n';
    }
}

const void ui_operations::filterPret(MedicamenteRepo &storage, int pret, char op) const {
    vector<Medicament>& vec_from = storage.get_all();
    vector<Medicament> vector_filtrat;
    vector_filtrat.clear();

    auto criteriu = [&pret, &op](Medicament& med){
                if(op == '>') return med.get_pret() > pret;
                if(op == '=') return med.get_pret() == pret;
                if(op == '<') return med.get_pret() < pret;
                return false;
    };

    std::copy_if(vec_from.begin(), vec_from.end(), std::back_inserter(vector_filtrat), criteriu);

    if(vector_filtrat.empty()) {
        std::cout << "Nu am gasit niciun medicament inregistrat care sa corespunda criteriilor!\n";
    }
    else {
        std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
        for(const auto & med : vector_filtrat) {
            print_one_med(med);
        }
    }
}

const void ui_operations::filterSubstActiva(MedicamenteRepo &storage, const string &subst) const {
    vector<Medicament>& vec_from = storage.get_all();
    vector<Medicament> vector_filtrat;
    vector_filtrat.clear();

    std::copy_if(vec_from.begin(), vec_from.end(), std::back_inserter(vector_filtrat),
                 [&subst](Medicament& med){return med.get_subst_activa() == subst;});

    if(vector_filtrat.empty()) {
        std::cout << "Nu am gasit niciun medicament inregistrat care sa corespunda criteriilor!\n";
    }
    else {
        std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
        for(const auto & med : vector_filtrat) {
            print_one_med(med);
        }
    }
}

const void ui_operations::genericSort(MedicamenteRepo &storage,
                                      function<int(const Medicament &, const Medicament &)> functie_comparare) const {
    vector<Medicament>& vec = storage.get_all();
    std::sort(vec.begin(), vec.end(), functie_comparare);

    std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
    for(const auto & med : vec) {
        print_one_med(med);
    }
}

const void ui_operations::print_raport(std::unordered_map<string, MedicamentDTO> &raport) {
    std::cout << "       RAPORT MEDICAMENTE\n";
    for(auto & it : raport) {
        std::cout << "Substanta activa: " << it.first << ", Numar medicamente: " << it.second.nr_meds << '\n';
    }
}
