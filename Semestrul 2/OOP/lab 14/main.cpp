#include <QApplication>
#include "MedicamentGUI.h"
#include "repository.h"
#include "service.h"

void test_all() {
    domainTests::test_getters_and_setters();
    repositoryTests::test_repository_functionalities();
    repositoryTests::test_new_repo_funct();
    file_repository_tests::test_all();
    validatorTests::validator_all_tests();
    serviceTests::run_all_servive_tests();
}

int main(int argc, char *argv[]) {
    test_all();

    QApplication a(argc, argv);

    Service serv;

    string file_name = "storage.txt";
    FileRepo repo{file_name};
    repo.load_from_file();

    MedicamenteRepo lista_reteta;

    MedicamentGUI app{serv, repo, lista_reteta};
    app.show();

    return QApplication::exec();
}
