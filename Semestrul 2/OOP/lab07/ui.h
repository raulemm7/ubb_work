//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_UI_H
#define LAB06_UI_H

#include <iostream>
#include <string>
#include <functional>
#include "domain.h"
#include "repository.h"
#include "definedVector.h"
using std::string;
using std::function;

class ui_operations {
public:
    /** afiseaza meniul aplicatiei */
    const void show_menu();

    /**
     * afiseaza un mesaj pe ecran
     * @param msg: mesajul care se doreste a fi afisat
     */
    const void show_message(const string& msg);

    /** afiseaza meniul pentru functionalitatea de filtrare */
    const void show_menu_for_filter() const;

    /** afiseaza meniul pentru functionalitatea de sortare */
    const void show_menu_for_sort() const;

    /**
     * afiseaza, formatat, informatiile unui medicament
     * @param medicament: medicamentul ale carui informatii se doresc a fi afisate
     */
    const void print_one_med(const Medicament& medicament) const;

    /**
     * afiseaza, formatat, informatiile medicamentelor dintr-o lista de medicamente
     * @param storage: lista de medicamente
     */
    const void print_meds(VectorDinamic<Medicament>& storage) const;

    /**
     * citeste o comanda de la tastatura (int)
     * @param MAX_COMMAND: numarul maxim care poate fi citit
     * @return: (int)nr, 0 <= nr <= MAX_COMMAND, nr citit de la tastatura
     */
    const int read_command(const int& MAX_COMMAND);

    /**
     * citeste un string de la tastatura
     * @param msg: mesaj care afiseaza informatii inainte de citire
     * @return: string citit de la tastatura
     */
    [[nodiscard]] const string citire_string(const string& msg) ;

    /**
     * citeste un pret de la tastatura
     * @param msg1: mesaj ce afiseaza informatii inainte de citire
     * @param msg2: mesaj ce afiseaza informatii in caz de eroare la citire
     * @return: (int)pret, pret > 5 citit de la tastatura
     */
    [[nodiscard]] const int citire_pret(const string& msg1, const string& msg2) ;

    /**
     * citeste un id de la tastatura
     * @param MAX_ID: id-ul maxim care poate fi citit de la tastatura
     * @param msg_out: mesaj ce afiseaza informatii inainte de citire
     * @param msg_err: mesaj ce afiseaza informatii in caz de eroare la citire
     * @return: (int)id, 0 <= id <= MAX_ID, id citit de la tastatura
     */
    const int read_id(const int& MAX_ID, const string& msg_out, const string& msg_err);

    /**
     * citeste informatiile unui medicament de la tastatura
     * @param id: id-ul care se va atribui noului medicament citit
     * @return: obiect de tip Medicament
     */
    const Medicament citire_medicament(const int& id) ;

    /**
     * afiseaza informatiile medicamentelor filtrate in functie de pret
     * @param storage: lista cu medicamente din care se face filtrarea
     * @param criteriu: criteriul dupa care se face filtrarea ('<', '=', '>')
     * @param suma: suma dupa care se face filtrarea
     */
    const void show_meds_filter_by_price(VectorDinamic<Medicament>& storage, const char& criteriu, const int& suma) const;

    /**
     * afiseaaza informatiile medicamentelor filtrate in functie de substanta activa
     * @param storage: lista cu medicamente din care se va face filtrarea
     * @param substanta: substanta dupa care se face filtrarea
     */
    const void show_meds_filter_by_subst(VectorDinamic<Medicament>& storage, const string& substanta) const;

    /**
     * citeste de la tastatura un operator ce reprezinta
     * criteriu pentru filtrarea in functie de pret ('<', '=', '>')
     * @param msg: mesaj ce afiseaza informatii inainte de citire
     * @param msg_err: mesaj ce afiseaza informatii in caz de eroare la citire
     * @return
     */
    const char citire_operator_filtrare(const string& msg, const string& msg_err);

    /**
     * afiseaza sortat elementele unui vector dupa un anumit criteriu
     * @param storage: containerul cu elemente
     * @param func: criteriul dupa care se face sortarea
     */
    const void oneCriteriaSort(VectorDinamic<Medicament> &storage, function<bool(const Medicament&, const Medicament&)> func) const;

    /**
     * afiseaza sortat elementele unui vector dupa doua criterii
     * @param storage: containerul cu elemente
     * @param function_1: primul criteriu dupa care se face sortarea
     * @param function_2: al doilea criteriu dupa care se face sortarea
     */
    const void twoCriteriaSort(VectorDinamic<Medicament> &storage, function<int(const Medicament&, const Medicament&)> function_1,
                               function<bool(const Medicament&, const Medicament&)> function_2) const;
};

#endif //LAB06_UI_H
