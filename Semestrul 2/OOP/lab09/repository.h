//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_REPOSITORY_H
#define LAB06_REPOSITORY_H

#include "domain.h"
#include <vector>
#include <map>
using std::vector;

#define REPO_TYPE MedicamenteRepoProbabilitate

class AbstractRepo {
public:
    virtual vector<Medicament>& get_all() = 0;

    virtual const int get_last_id() const = 0;

    virtual const Medicament& get_med(const int& position) const = 0;

    virtual const void adauga_medicament(const Medicament& medicament) = 0;

    virtual const void sterge_medicament(const int& id_med) = 0;

    virtual const void modifica_medicament(const int& id_med, const int& new_pret, const string& new_subst_activa) = 0;

    virtual const void set_id_correctly() = 0;

    virtual ~AbstractRepo() = default;
};

/**
 * clasa de storage a informatiilor
 */
class MedicamenteRepo : public AbstractRepo {
private:
    vector<Medicament> lista_meds;
    int nr_medicamente;
public:
    /** constructorul clasei */
    MedicamenteRepo();

    /** returneaza lista propriu-zisa de medicamente */
    vector<Medicament>& get_all() override;

    /** returneaza numarul de medicamente inregistrate */
    const int get_last_id() const override;

    /**
     * returneaza un medicament de pe o pozitie specificata
     * @param position: pozitia medicamentului din lista de medicamente
     * @return: obiect de tip Medicament
     */
    const Medicament& get_med(const int& position) const override;

    /**
     * adaugare medicament in lista curenta
     * @param medicament: medicamentul care se va adauga
     */
    const void adauga_medicament(const Medicament& medicament) override;

    /**
     * stergerea unui medicament din lista curenta
     * @param id_med: id-ul medicamentului care se va sterge
     */
    const void sterge_medicament(const int& id_med) override;

    /**
     * modificarea unui medicament din lista curenta
     * @param id_med: id-ul medicamentului care se va modifica
     * @param new_pret: noul pret al medicamentului
     * @param new_subst_activa: noua substanta activa a medicamentului
     */
    const void modifica_medicament(const int& id_med, const int& new_pret, const string& new_subst_activa) override;

    /**
     * seteaza tuturor medicamentelor din lista curenta
     * id-ul corespunzator pozitiei lor in lista
     */
    const void set_id_correctly() override;

    ~MedicamenteRepo() override = default;
};

class MedicamenteRepoProbabilitate : public AbstractRepo {
private:
    float nr_probabilitate;
    int nr_meds;
    std::map<int, Medicament> lista_meds;
    vector<Medicament> medicamente;
    void probabilitate() const;
public:
    MedicamenteRepoProbabilitate() : nr_probabilitate{1.0}{};

    explicit MedicamenteRepoProbabilitate(float prob);

    vector<Medicament>& get_all() override;

    const int get_last_id() const override;

    const Medicament& get_med(const int& position) const override;

    const void adauga_medicament(const Medicament& medicament) override;

    const void sterge_medicament(const int& id_med) override;

    const void modifica_medicament(const int& id_med, const int& new_pret, const string& new_subst_activa) override;

    const void set_id_correctly() override;

    ~MedicamenteRepoProbabilitate() override = default;
};

class FileRepository:public MedicamenteRepo {
private:
    string file_name;
    REPO_TYPE storage;
public:
    FileRepository() = default;
    explicit FileRepository(string ceva_string) {
        this->file_name = std::move(ceva_string);
    };

    void load_from_file();
    void save_on_file();

    const void adauga_medicament(const Medicament& medicament) override {
        this->storage.adauga_medicament(medicament);
        this->save_on_file();
    };

    const void sterge_medicament(const int& id_med) override {
        this->storage.sterge_medicament(id_med);
        this->storage.set_id_correctly();
        this->save_on_file();
    };

    const void modifica_medicament(const int& id_med, const int& new_pret, const string& new_subst_activa) override {
        this->storage.modifica_medicament(id_med, new_pret, new_subst_activa);
        this->save_on_file();
    };

    ~FileRepository() override = default;
};

class repositoryTests{
public:
    const static void test_repository_functionalities();
    const static void test_new_repo_funct();
};

#endif //LAB06_REPOSITORY_H
