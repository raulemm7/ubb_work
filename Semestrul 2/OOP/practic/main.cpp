#include <QApplication>
#include "MasinaGUI.h"
#include <iostream>

void test_all(){
    TestDomain::test_all();
    TestRepo::test_all();
    TestService::test_all();
    std::cout << "Passed all tests!\n";
}

int main(int argc, char *argv[]) {
    test_all();

    QApplication a(argc, argv);

    Service serv;

    std::string filename = "storage.txt";
    RepoMasina repo{filename};
    repo.load_from_file();

    MasinaGUI app{serv, repo};
    app.show();

    return QApplication::exec();
}
