//
// Created by raulo on 4/2/2024.
//

#include "ui.h"
#include "domain.h"
#include <numeric>

const void ui_operations::show_menu() {
    std::cout << "1. Adauga medicament\n";
    std::cout << "2. Sterge medicament\n";
    std::cout << "3. Modifica medicament\n";
    std::cout << "4. Afisare medicamente\n";
    std::cout << "5. Cautare medicament\n";
    std::cout << "6. Filtrare medicamente\n";
    std::cout << "7. Sortare medicamente\n";
    std::cout << "8. Iesire din aplicatie\n";
    std::cout << "0. Adaugare rapida (adauga 3 medicamente)\n";
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

const void ui_operations::print_meds(VectorDinamic<Medicament>& storage) const{
    std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
    for(int i = 0; i < storage.get_last_id_vd(); i++) {
        const Medicament& med = storage.get_element(i);
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

const Medicament ui_operations::citire_medicament(const int &id) {
    string denumire = citire_string("Introdu denumirea noului medicament: ");
    int pret = citire_pret("Introdu pretul noului medicament: ", "Introdu un pret corect!");
    string producator = citire_string("Introdu producatorul noului medicament: ");
    string subst_activa = citire_string("Introdu substanta activa a noului medicament: ");

    Medicament med(id, denumire, pret, producator, subst_activa);
    return med;
}

const void ui_operations::show_meds_filter_by_price(VectorDinamic<Medicament> &storage, const char &criteriu, const int &suma) const {
    bool ok = false;

    for(int i = 0; i < storage.get_last_id_vd(); i++) {
        const Medicament& med = storage.get_element(i);

        if(criteriu == '=') {
            if(med.get_pret() == suma) {
                if(!ok) {
                    std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
                    ok = true;
                }
                print_one_med(med);
            }
        }
        if(criteriu == '<') {
            if(med.get_pret() < suma) {
                if(!ok) {
                    std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
                    ok = true;
                }
                print_one_med(med);
            }
        }
        if(criteriu == '>') {
            if(med.get_pret() > suma) {
                if(!ok) {
                    std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
                    ok = true;
                }
                print_one_med(med);
            }
        }
    }
    if(!ok) {
        std::cout << "Nu am gasit niciun medicament inregistrat care sa corespunda criteriilor!\n";
    }
}

const void ui_operations::show_meds_filter_by_subst(VectorDinamic<Medicament> &storage, const string &substanta) const {
    bool ok = false;
    for(int i = 0; i < storage.get_last_id_vd(); i++) {
        const Medicament& med = storage.get_element(i);

        if(med.get_subst_activa() == substanta) {
            if(!ok) {
                std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
                ok = true;
            }
            print_one_med(med);
        }
    }

    if(!ok) {
        std::cout << "Nu am gasit niciun medicament inregistrat care sa corespunda criteriilor!\n";
    }
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

const void ui_operations::oneCriteriaSort(VectorDinamic<Medicament> &storage, function<bool(const Medicament&, const Medicament&)> func) const {
    // initializare vector de pozitii
    int vector_de_pozitii[storage.get_last_id_vd()];
    for(int i = 0; i < storage.get_last_id_vd(); i++)
        vector_de_pozitii[i] = i;

    // sortare
    for(int i = 0; i < storage.get_last_id_vd() - 1; i++) {
        for(int j = i + 1; j < storage.get_last_id_vd(); j++) {
            // med_i.criteriu > med_j.criteriu
            const Medicament& med_i = storage.get_element(vector_de_pozitii[i]);
            const Medicament& med_j = storage.get_element(vector_de_pozitii[j]);

            if(func(med_i, med_j) == 1) {
                int aux = vector_de_pozitii[i];
                vector_de_pozitii[i] = vector_de_pozitii[j];
                vector_de_pozitii[j] = aux;
            }
        }
    }

    // afisare
    std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
    for(int i = 0; i < storage.get_last_id_vd(); i++) {
        const Medicament& med = storage.get_element(vector_de_pozitii[i]);
        print_one_med(med);
    }
}

const void ui_operations::twoCriteriaSort(VectorDinamic<Medicament> &storage,
                                          function<int(const Medicament &, const Medicament &)> function_1,
                                          function<bool(const Medicament &, const Medicament &)> function_2) const {
    // initializare vector de pozitii
    int vector_de_pozitii[storage.get_last_id_vd()];
    for(int i = 0; i < storage.get_last_id_vd(); i++)
        vector_de_pozitii[i] = i;

    // sortare
    for(int i = 0; i < storage.get_last_id_vd() - 1; i++) {
        for(int j = i + 1; j < storage.get_last_id_vd(); j++) {
            // med_i.criteriu > med_j.criteriu
            const Medicament& med_i = storage.get_element(vector_de_pozitii[i]);
            const Medicament& med_j = storage.get_element(vector_de_pozitii[j]);

            // verific dupa primul criteriu
            if(function_1(med_i, med_j) == 1) {
                // swap
                int aux = vector_de_pozitii[i];
                vector_de_pozitii[i] = vector_de_pozitii[j];
                vector_de_pozitii[j] = aux;
            }
            else if(function_1(med_i, med_j) == 0 and function_2(med_i, med_j)) {
                // swap
                int aux = vector_de_pozitii[i];
                vector_de_pozitii[i] = vector_de_pozitii[j];
                vector_de_pozitii[j] = aux;
            }
        }
    }

    // afisare
    std::cout << "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";
    for(int i = 0; i < storage.get_last_id_vd(); i++) {
        const Medicament& med = storage.get_element(vector_de_pozitii[i]);
        print_one_med(med);
    }
}
