#include <QApplication>

#include "domain.h"
#include "repository.h"
#include "service.h"
#include "validator.h"
#include "ImbracaminteGUI.h"

void test_all(){
    testDomain::test_all();
    testStorage::test_all();
    testService::test_all();
    ValidatorTest::test_all();
}

int main(int argc, char *argv[]) {
    test_all();

    QApplication a(argc, argv);

    string file_name = "storage.txt";
    Repository storage{file_name};
    storage.load_from_file();

    Service service;

    ImbracaminteGUI app{storage, service};
    app.show();

    return QApplication::exec();
}
