#include <QApplication>
#include "MedicamentGUI.h"
#include "repository.h"
#include "service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Service serv;
    MedicamenteRepo repo;
    MedicamentGUI app{serv, repo};
    app.show();

    return QApplication::exec();
}
