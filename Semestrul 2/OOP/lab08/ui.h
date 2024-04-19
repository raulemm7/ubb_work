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

    /** afiseaza meniul pentru functionalitatea retetei */
    const void show_menu_for_prescription();

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
    const void print_meds(MedicamenteRepo& storage, const string& header) const;

    /**
     * citeste o comanda de la tastatura (int)
     * @param MAX_COMMAND: numarul maxim care poate fi citit
     * @return: (int)nr, 0 <= nr <= MAX_COMMAND, nr citit de la tastatura
     */
    const int read_command(const int& MAX_COMMAND);

    /**
     * citeste numele fisierului in care vor fi salvate datele
     * @return: string
     */
    string read_name_file();

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
     * citeste de la tastatura denumirea unui medicament existent in storage
     * @param storage lista cu medicamente
     * @param msg_out mesajul de informare a utilizatorului
     * @param msg_err mesaj de eroare
     * @return (int) id-ul medicamentului din storage
     */
    const int read_id_with_string(MedicamenteRepo& storage, const string& msg_out, const string& msg_err);

    /**
     * citeste informatiile unui medicament de la tastatura
     * @param id: id-ul care se va atribui noului medicament citit
     * @return: obiect de tip Medicament
     */
    const Medicament citire_medicament(const int& id) ;

    /**
     * citeste de la tastatura un operator ce reprezinta
     * criteriu pentru filtrarea in functie de pret ('<', '=', '>')
     * @param msg: mesaj ce afiseaza informatii inainte de citire
     * @param msg_err: mesaj ce afiseaza informatii in caz de eroare la citire
     * @return
     */
    const char citire_operator_filtrare(const string& msg, const string& msg_err);

    /**
     * afiseaza informatiile medicamentelor filtrate in functie de pret
     * @param storage: lista cu medicamente din care se face filtrarea
     * @param pret: suma dupa care se face filtrarea
     * @param op: criteriul dupa care se face filtrarea ('<', '=', '>')
     */
    const void filterPret(MedicamenteRepo &storage, int pret, char op) const;

    /**
     * afiseaaza informatiile medicamentelor filtrate in functie de substanta activa
     * @param storage: lista cu medicamente din care se va face filtrarea
     * @param subst: substanta dupa care se face filtrarea
     */
    const void filterSubstActiva(MedicamenteRepo &storage, const string& subst) const;

    /**
     * functie ce afiseaza, sortat dupa un criteriu dat, informatiile medicamentelor
     * @param storage lista cu medicamente
     * @param functie_comparare criteriul dupa care se face comapararea
     */
    const void genericSort(MedicamenteRepo &storage, function<int(const Medicament&, const Medicament&)> functie_comparare) const;

    const void print_raport(std::unordered_map<string, MedicamentDTO>& raport);
};

#endif //LAB06_UI_H
