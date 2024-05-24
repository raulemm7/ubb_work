#include <QApplication>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "pixGUI.h"
#include "validators.h"

int main(int argc, char *argv[]) {
    testDomain::test_all();
    testValidator::test_all();
    testService::test_all();
    testRepo::test_all();

    QApplication a(argc, argv);

    string nume_fisier = "storage.txt";
    Repository storage{nume_fisier};
    storage.load_from_file();

    Service service;

    pixGUI app{storage, service};
    app.show();

    return QApplication::exec();
}
