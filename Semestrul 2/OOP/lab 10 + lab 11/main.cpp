#include <QApplication>
#include "MedicamentGUI.h"
#include "repository.h"
#include "service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Service serv;

    string file_name = "storage.txt";
    FileRepo repo{file_name};
    repo.load_from_file();

    MedicamentGUI app{serv, repo};
    app.show();

    return QApplication::exec();
}
