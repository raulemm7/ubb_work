//
// Created by raulo on 4/2/2024.
//

#include "service.h"
#include "iteratorVector.h"
#include <cassert>
#include <bitset>
#include <fstream>
#include <random>

const string Service::adaugaMedicament(MedicamenteRepo& storage, const Medicament& medicament) {
    Validator vali;
    if(vali.valideaza_med(storage, medicament)) {
        std::cout << "->";
        storage.adauga_medicament(medicament);
        return "Medicament adaugat cu succes!";
    }
    return "Acest medicament exista deja!";
}

const string Service::stergeMedicament(MedicamenteRepo &storage, const int &id_medicament) {
    storage.sterge_medicament(id_medicament);
    return "Medicament sters cu succes!";
}

const string Service::stergeToateMedicamentele(MedicamenteRepo &storage) {
    while(storage.get_last_id()) {
        storage.sterge_medicament(0);
        storage.set_id_correctly();
    }

    return "Toate medicamentele au fost sterse cu succes!";
}

const string Service::modificaMedicament(MedicamenteRepo &storage, const int &id_medicament, const int& new_pret,
                                   const string& new_subst_activa) {
    storage.modifica_medicament(id_medicament, new_pret, new_subst_activa);
    return "Medicament modificat cu succes!";
}

const string Service::cautaMedicament(MedicamenteRepo &storage, const string &search) {
    vector<Medicament>& vec = storage.get_all();

    auto eq_denumire = [&search](Medicament& med) {return med.get_denumire() == search;};
    auto it = std::find_if(vec.begin(), vec.end(), eq_denumire);

    if(it == vec.end())
        return "Nu am gasit niciun medicament inregistrat cu aceasta denumire!";
    else {
        ui_operations ui;
        ui.show_message("  ID  |  DENUMIRE  |  PRET  |  PRODUCATOR  |  SUBST. ACTIVA");
        ui.print_one_med(*it);
        return "Medicament gasit si afisat cu succes!";
    }
}

const string Service::adaugaMedicamenteRapid(MedicamenteRepo &storage) {
    Medicament med0(0, "brufen", 25, "pharma", "paracetamol");
    adaugaMedicament(storage, med0);

    Medicament med1(1, "lecitina", 34, "boiron", "soia");
    adaugaMedicament(storage, med1);

    Medicament med2(2, "algolcalmin", 19, "walmark", "paracetamol");
    adaugaMedicament(storage, med2);

    Medicament med3(3, "acc", 36, "sandoz", "plante");
    adaugaMedicament(storage, med3);

    Medicament med4(4, "nurofen", 22, "boiron", "paracetamol");
    adaugaMedicament(storage, med4);

    Medicament med5(5, "aspacardin", 20, "terapia", "minerale");
    adaugaMedicament(storage, med5);

    Medicament med6(6, "aspenter", 15, "bayer", "minerale");
    adaugaMedicament(storage, med6);

    Medicament med7(7, "aspirin", 13, "bayer", "paracetamol");
    adaugaMedicament(storage, med7);

    Medicament med8(8, "bromehxin", 26, "sandoz", "plante");
    adaugaMedicament(storage, med8);

    Medicament med9(9, "faringosept", 31, "pharma", "plante");
    adaugaMedicament(storage, med9);

    return "Medicamente adaugate cu succes";
}

const string
Service::exportDataInHTMLformat(MedicamenteRepo &storage, const string &file_name, int prescription_number) {
    const string HTML_BEGIN = "<!DOCTYPE html>\n<html  lang=\"ro\">\n<style>\n    table, th, td { \n        border:1px "
                              "\n        solid black; \n        text-align: center; \n    }"
                              "\n    table.center { \n        margin-left: auto; \n        margin-right: auto; \n    } "
                              "\n</style>\n<head>\n    <title>Reteta</title>\n</head>\n<body>";
    const string HTML_END = "\n</body>\n</html>";
    const string HTML_TABLE_HEADER_BEGIN = "\n            <th>";
    const string HTML_TABLE_HEADER_END = "</th>";
    const string HTML_TABLE_ROW_BEGGIN = "\n        <tr>";
    const string HTML_TABLE_ROW_END = "\n        </tr>";
    const string HTML_TABLE_CELL_BEGIN = "\n            <td>";
    const string HTML_TABLE_CELL_END = "</td>";
    const string DOC_HEADER = "\n    <h2  style=\"text-align: center\">Reteta numarul " + std::to_string(prescription_number) + "</h2>";

    std::ofstream out_in_file(file_name);

    // insert in file
    out_in_file << HTML_BEGIN;
    out_in_file << DOC_HEADER;

    // create table
    out_in_file << "\n    <table class=\"center\" style=\"width:75%\">";

    // create table header
    string TABLE_HEADER;
    TABLE_HEADER += HTML_TABLE_ROW_BEGGIN;
    TABLE_HEADER += HTML_TABLE_HEADER_BEGIN;
    TABLE_HEADER += "Numar medicament";
    TABLE_HEADER += HTML_TABLE_HEADER_END;
    TABLE_HEADER += HTML_TABLE_HEADER_BEGIN;
    TABLE_HEADER += "Denumire";
    TABLE_HEADER += HTML_TABLE_HEADER_END;
    TABLE_HEADER += HTML_TABLE_HEADER_BEGIN;
    TABLE_HEADER += "Producator";
    TABLE_HEADER += HTML_TABLE_HEADER_END;
    TABLE_HEADER += HTML_TABLE_HEADER_BEGIN;
    TABLE_HEADER += "Substanta activa";
    TABLE_HEADER += HTML_TABLE_HEADER_END;
    TABLE_HEADER += HTML_TABLE_HEADER_BEGIN;
    TABLE_HEADER += "Pret";
    TABLE_HEADER += HTML_TABLE_HEADER_END;
    TABLE_HEADER += HTML_TABLE_ROW_END;

    out_in_file << TABLE_HEADER;

    for(int i = 0; i < storage.get_last_id(); i++) {
        const Medicament& med = storage.get_med(i);

        // meds info -> text
        string med_text;

        med_text += HTML_TABLE_ROW_BEGGIN;
        med_text += HTML_TABLE_CELL_BEGIN;
        med_text += std::to_string(i + 1);
        med_text += HTML_TABLE_CELL_END;
        med_text += HTML_TABLE_CELL_BEGIN;
        med_text += med.get_denumire();
        med_text += HTML_TABLE_CELL_END;
        med_text += HTML_TABLE_CELL_BEGIN;
        med_text += med.get_producator();
        med_text += HTML_TABLE_CELL_END;
        med_text += HTML_TABLE_CELL_BEGIN;
        med_text += med.get_subst_activa();
        med_text += HTML_TABLE_CELL_END;
        med_text += HTML_TABLE_CELL_BEGIN;
        med_text += std::to_string(med.get_pret());
        med_text += HTML_TABLE_CELL_END;
        med_text += HTML_TABLE_ROW_END;

        out_in_file << med_text;
    }

    // close table
    out_in_file << "\n    </table>";

    // close html
    out_in_file << HTML_END;
    out_in_file.close();

    return "Fisier creat cu succes!\nLocatia fisierului: D:/oop/lab06/cmake-build-debug/" + file_name;
}

const string Service::adaugareRandom(MedicamenteRepo &storage_with_meds, MedicamenteRepo& reteta, int numar_medicamente) {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, storage_with_meds.get_last_id() - 1);

    for(int i = 0; i < numar_medicamente; i++) {
        // generez numar random
        int randomNumber = dist(mt);

        const Medicament& med = storage_with_meds.get_med(randomNumber);
        const string& msgoutput = adaugaMedicament(reteta, med);
        if(msgoutput == "Acest medicament exista deja!")
            i--;
    }

    return "Medicamente adaugate cu succes!";
}

const void serviceTests::run_all_servive_tests() {
    test_adaugaMedicament();
    test_cautaMedicament();
    test_modificaMedicament();
    test_stergeMedicament();
    test_stergeToateMedicamentele();
    test_exportDataInHTMLformat();
    test_adaugareRapida_and_adaugareRandom();
}

const void serviceTests::test_adaugaMedicament() {
    Service service;

    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    assert(service.adaugaMedicament(storage, med) == "Medicament adaugat cu succes!");
    assert(service.adaugaMedicament(storage, med) == "Acest medicament exista deja!");

    // adaug mult pentru a verifica
    // daca se executa corect realocarea de memorie
    for(int i = 1; i <= 20; i++) {
        Medicament med1(i, "adsda", 20 + i, "dsadada", "asddaa");
        service.adaugaMedicament(storage, med1);
    }
    // verific numarul de elemente din storage
    assert(storage.get_last_id() == 21);
}

const void serviceTests::test_stergeMedicament() {
    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.stergeMedicament(storage, 0) == "Medicament sters cu succes!");
}

const void serviceTests::test_stergeToateMedicamentele() {
    Service service;

    MedicamenteRepo storage;
    service.adaugaMedicamenteRapid(storage);
    assert(storage.get_last_id() == 10);

    service.stergeToateMedicamentele(storage);
    assert(storage.get_last_id() == 0);
}

const void serviceTests::test_modificaMedicament() {
    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.modificaMedicament(storage, 0, 26, "alta_substanta") == "Medicament modificat cu succes!");
}

const void serviceTests::test_cautaMedicament() {
    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.cautaMedicament(storage, "algolcalmin") == "Medicament gasit si afisat cu succes!");
    assert(service.cautaMedicament(storage, "paramataciol") == "Nu am gasit niciun medicament inregistrat cu aceasta denumire!");
}

const void serviceTests::test_exportDataInHTMLformat() {
    Service service;
    MedicamenteRepo storage;
    service.adaugaMedicamenteRapid(storage);

    const string& rezultat = service.exportDataInHTMLformat(storage, "fisier_test.html", 0);
    assert(rezultat == "Fisier creat cu succes!\nLocatia fisierului: D:/oop/lab06/cmake-build-debug/fisier_test.html");
}

const void serviceTests::test_adaugareRapida_and_adaugareRandom() {
    Service service;

    MedicamenteRepo storage;
    service.adaugaMedicamenteRapid(storage);
    MedicamenteRepo reteta;

    const string& rezultat = service.adaugareRandom(storage, reteta, 5);
    assert(rezultat == "Medicamente adaugate cu succes!");
    assert(reteta.get_last_id() == 5);
}
