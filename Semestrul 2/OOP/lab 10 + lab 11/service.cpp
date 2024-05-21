//
// Created by raulo on 4/2/2024.
//

#include "service.h"
#include <cassert>
#include <bitset>
#include <fstream>
#include <random>

#define REPO_TYPE MedicamenteRepoProbabilitate

const string Service::adaugaMedicament(AbstractRepo& storage, const Medicament& medicament) {
    Validator vali;
    if(vali.valideaza_med(storage, medicament)) {
        std::cout << "->";
        storage.adauga_medicament(medicament);
        this->undo_list.push_back(std::make_unique<undo_adauga>(storage, medicament.get_id()));
        return "Medicament adaugat cu succes!";
    }

    return "Acest medicament exista deja!";
}

const string Service::stergeMedicament(AbstractRepo &storage, const int &id_medicament) {
    const Medicament& med = storage.get_med(id_medicament);
    this->undo_list.push_back(std::make_unique<undo_sterge>(storage, med));

    storage.sterge_medicament(id_medicament);
    return "Medicament sters cu succes!";
}

const string Service::stergeToateMedicamentele(AbstractRepo &storage) {
    while(storage.get_last_id()) {
        storage.sterge_medicament(0);
        storage.set_id_correctly();
    }

    return "Toate medicamentele au fost sterse cu succes!";
}

const string Service::modificaMedicament(AbstractRepo &storage, const int &id_medicament, const int& new_pret,
                                   const string& new_subst_activa) {
    const Medicament& med = storage.get_med(id_medicament);
    this->undo_list.push_back(std::make_unique<undo_modifica>(storage, med, med.get_pret(), med.get_subst_activa()));

    storage.modifica_medicament(id_medicament, new_pret, new_subst_activa);
    return "Medicament modificat cu succes!";
}

int Service::cautaMedicament(AbstractRepo &storage, const string &search) {
    vector<Medicament>& vec = storage.get_all();

    auto eq_denumire = [&search](Medicament& med) {return med.get_denumire() == search;};
    auto it = std::find_if(vec.begin(), vec.end(), eq_denumire);

    if(it == vec.end())
        return -1;
    else {
        ui_operations ui;
        ui.show_message("  ID  |  DENUMIRE  |  PRET  |  PRODUCATOR  |  SUBST. ACTIVA");
        ui.print_one_med(*it);
        return it->get_id();
    }
}

const string Service::adaugaMedicamenteRapid(AbstractRepo &storage) {
    Medicament med0(storage.get_last_id(), "brufen", 25, "pharma", "paracetamol");
    this->adaugaMedicament(storage, med0);
    storage.set_id_correctly();
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med1(storage.get_last_id(), "lecitina", 34, "boiron", "soia");
    this->adaugaMedicament(storage, med1);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med2(storage.get_last_id(), "algolcalmin", 19, "walmark", "paracetamol");
    this->adaugaMedicament(storage, med2);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med3(storage.get_last_id(), "acc", 36, "sandoz", "plante");
    this->adaugaMedicament(storage, med3);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med4(storage.get_last_id(), "nurofen", 22, "boiron", "paracetamol");
    this->adaugaMedicament(storage, med4);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med5(storage.get_last_id(), "aspacardin", 20, "terapia", "minerale");
    this->adaugaMedicament(storage, med5);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med6(storage.get_last_id(), "aspenter", 15, "bayer", "minerale");
    this->adaugaMedicament(storage, med6);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med7(storage.get_last_id(), "aspirin", 13, "bayer", "paracetamol");
    this->adaugaMedicament(storage, med7);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med8(storage.get_last_id(), "bromehxin", 26, "sandoz", "plante");
    this->adaugaMedicament(storage, med8);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    Medicament med9(storage.get_last_id(), "faringosept", 31, "pharma", "plante");
    this->adaugaMedicament(storage, med9);
    this->undo_list.push_back(std::make_unique<undo_adauga>(storage, storage.get_last_id() - 1));

    return "Medicamente adaugate cu succes";
}

const string
Service::exportDataInHTMLformat(AbstractRepo &storage, const string &file_name, int prescription_number) {
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

const string Service::adaugareRandom(AbstractRepo &storage_with_meds, AbstractRepo& reteta, int numar_medicamente) {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, storage_with_meds.get_last_id() - 1);

    for(int i = 0; i < numar_medicamente; i++) {
        // generez numar random
        int randomNumber = dist(mt);

        const Medicament& med = storage_with_meds.get_med(randomNumber);
        reteta.adauga_medicament(med);
    }

    return "Medicamente adaugate cu succes!";
}

std::unordered_map<string, MedicamentDTO> Service::generareRaport(AbstractRepo &storage) {
    vector<Medicament>& vectorMeds = storage.get_all();
    std::unordered_map<string, MedicamentDTO> raport;

    for(const auto &med : vectorMeds) {
        const string& subst_activa = med.get_subst_activa();
        if(raport.find(subst_activa) != raport.end())
            raport[subst_activa].nr_meds += 1;
        else
            raport[subst_activa] = MedicamentDTO(subst_activa, 1);
    }

    return raport;
}

const string Service::executa_undo(AbstractRepo& storage) {
    if(this->undo_list.empty()) {
        return "Nu se mai poate face undo!";
    }
    storage = this->undo_list.back()->do_undo();
    this->undo_list.pop_back();
    return "Undo efectuat cu succes!";
}

const string Service::load_data_from_txt(FileRepo &storage) {
    storage.load_from_file();
    for(int i = 0; i < storage.get_last_id(); i++) {
        this->undo_list.push_back(std::make_unique<undo_adauga>(storage, i));
    }
    return "Au fost adaugate cu succes " + std::to_string(storage.get_last_id()) + " medicamente";
}

const string Service::store_data_in_txt(FileRepo &storage) {
    storage.clear_file();
    storage.save_to_file();

    return "Medicamentele au fost salvate cu succes in fisier!";
}

vector<Medicament> Service::sortare_generica(AbstractRepo &storage,
                                     function<int(const Medicament &, const Medicament &)> functie_comparare) {
    vector<Medicament>& vec = storage.get_all();
    std::sort(vec.begin(), vec.end(), functie_comparare);
    return vec;
}

vector<Medicament> Service::filtrare_dupa_substanta(AbstractRepo &storage, const string &subst) {
    vector<Medicament>& vec_from = storage.get_all();
    vector<Medicament> vector_filtrat;
    vector_filtrat.clear();

    std::copy_if(vec_from.begin(), vec_from.end(), std::back_inserter(vector_filtrat),
                 [&subst](Medicament& med){return med.get_subst_activa() == subst;});

    return vector_filtrat;
}

vector<Medicament> Service::filtrare_dupa_pret(AbstractRepo &storage, int pret, char op) {
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

    return vector_filtrat;
}

const void serviceTests::run_all_servive_tests() {
    test_adaugaMedicament();
    test_cautaMedicament();
    test_modificaMedicament();
    test_stergeMedicament();
    test_stergeToateMedicamentele();
    test_exportDataInHTMLformat();
    test_adaugareRapida_and_adaugareRandom();
    test_generareRaport();
    test_executa_undo();
    test_upload_to_txt();
    test_load_from_txt();
}

const void serviceTests::test_adaugaMedicament() {
    Service service;

    REPO_TYPE storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    assert(service.adaugaMedicament(storage, med) == "Medicament adaugat cu succes!");
    assert(service.adaugaMedicament(storage, med) == "Acest medicament exista deja!");

}

const void serviceTests::test_stergeMedicament() {
    REPO_TYPE storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.stergeMedicament(storage, 0) == "Medicament sters cu succes!");
}

const void serviceTests::test_stergeToateMedicamentele() {
    Service service;

    REPO_TYPE storage;
    service.adaugaMedicamenteRapid(storage);
    assert(storage.get_last_id() == 10);

    service.stergeToateMedicamentele(storage);
    assert(storage.get_last_id() == 0);
}

const void serviceTests::test_modificaMedicament() {
    REPO_TYPE storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.modificaMedicament(storage, 0, 26, "alta_substanta") == "Medicament modificat cu succes!");
}

const void serviceTests::test_cautaMedicament() {
    REPO_TYPE storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.cautaMedicament(storage, "algolcalmin") == 0);
    assert(service.cautaMedicament(storage, "paramataciol") == -1);
}

const void serviceTests::test_exportDataInHTMLformat() {
    Service service;
    REPO_TYPE storage;
    service.adaugaMedicamenteRapid(storage);

    const string& rezultat = service.exportDataInHTMLformat(storage, "fisier_test.html", 0);
    assert(rezultat == "Fisier creat cu succes!\nLocatia fisierului: D:/oop/lab06/cmake-build-debug/fisier_test.html");
}

const void serviceTests::test_adaugareRapida_and_adaugareRandom() {
    Service service;

    REPO_TYPE storage;
    service.adaugaMedicamenteRapid(storage);
    REPO_TYPE reteta;

    const string& rezultat = service.adaugareRandom(storage, reteta, 5);
    assert(rezultat == "Medicamente adaugate cu succes!");
    assert(reteta.get_last_id() == 5);
}

const void serviceTests::test_generareRaport() {
    Service service;

    REPO_TYPE storage;
    Medicament med0(0, "brufen", 25, "pharma", "paracetamol");
    service.adaugaMedicament(storage, med0);

    Medicament med1(1, "lecitina", 34, "boiron", "soia");
    service.adaugaMedicament(storage, med1);

    Medicament med2(2, "algolcalmin", 19, "walmark", "paracetamol");
    service.adaugaMedicament(storage, med2);

    std::unordered_map<string, MedicamentDTO> raport = service.generareRaport(storage);

    assert(!raport.empty());

    auto it = raport.begin();
    assert(it != raport.end());
    assert(it->first == "soia");
    assert(it->second.nr_meds == 1);

    it++;
    assert(it != raport.end());
    assert(it->first == "paracetamol");
    assert(it->second.nr_meds == 2);

    it++;
    assert(it == raport.end());
}

const void serviceTests::test_executa_undo() {
    Service service;
    REPO_TYPE repo;

    assert(service.executa_undo(repo) == "Nu se mai poate face undo!");

    Medicament med{0, "dsada", 323, "dasda", "sdadas"};
    service.adaugaMedicament(repo, med);
    Medicament med1{1, "fdfsf", 34, "gdsfa", "fdsf"};
    service.adaugaMedicament(repo, med1);
    assert(repo.get_last_id() == 2);

    // sterg un med
    string msj_ = service.stergeMedicament(repo, 0);
    assert(msj_ == "Medicament sters cu succes!");
    assert(repo.get_last_id() == 1);

    msj_ = service.executa_undo(repo);
    repo.set_id_correctly();
    assert(msj_ == "Undo efectuat cu succes!");
    assert(repo.get_last_id() == 2);

    // modific un med
    msj_ = service.modificaMedicament(repo, 0, 300, "alf");
    assert(msj_ == "Medicament modificat cu succes!");
    Medicament medc = repo.get_med(0);
    assert(medc.get_pret() == 300);
    assert(medc.get_subst_activa() == "alf");

    msj_ = service.executa_undo(repo);
    assert(msj_ == "Undo efectuat cu succes!");
    medc = repo.get_med(0);
    ui_operations ui;
    ui.print_one_med(medc);
    assert(medc.get_pret() == 34);
    assert(medc.get_subst_activa() == "fdsf");

    // undo adauga
    msj_ = service.executa_undo(repo);
    assert(msj_ == "Undo efectuat cu succes!");
    std::cout << repo.get_last_id();
    assert(repo.get_last_id() == 1);
}

const void serviceTests::test_load_from_txt() {
    Service service;
    FileRepo repo("fisier_cu_3_meds.txt");

//    service.load_data_from_txt(repo);

//    assert(repo.get_last_id() == 3);
//    assert(service.executa_undo(repo) == "Undo efectuat cu succes!");

    return;
}

const void serviceTests::test_upload_to_txt() {
    Service service;
    FileRepo repo("fisier_upl.txt");

    repo.clear_file();

    Medicament med1(0, "brufen", 25, "pharma", "paracetamol");
    repo.adauga_medicament(med1);

    Medicament med2(1, "lecitina", 34, "boiron", "soia");
    repo.adauga_medicament(med2);

    Medicament med3(2, "acc", 36, "sandoz", "plante");
    repo.adauga_medicament(med3);

    assert(repo.get_last_id() == 3);

    service.store_data_in_txt(repo);

    FileRepo repo_upl("fisier_upl.txt");
    service.load_data_from_txt(repo_upl);

    assert(repo_upl.get_last_id() == 3);
    assert(repo_upl.get_med(0).get_denumire() == "brufen");
    assert(repo_upl.get_med(1).get_denumire() == "lecitina");
    assert(repo_upl.get_med(2).get_denumire() == "acc");

    repo.clear_file();
}
