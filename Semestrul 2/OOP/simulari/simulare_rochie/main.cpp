#include <QApplication>
#include <QPushButton>

#include "domain.h"
#include "repository.h"
#include "service.h"
#include "RochieGUI.h"

void test_all(){
    testDomain::test_all();
}

int main(int argc, char *argv[]) {
    test_all();

    QApplication a(argc, argv);

    string nume_fisier = "storage.txt";
    Repository storage{nume_fisier};
    storage.load_from_file();

    Service service;

    rochieGUI app{storage, service};
    app.show();

    return QApplication::exec();
}
