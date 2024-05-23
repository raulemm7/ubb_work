#include <QApplication>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "server_log_GUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    test_domain::test_all();
    test_repository::test_all();

    string file_name = "storage.txt";
    repository storage{file_name};
    storage.load_from_file();

    Service service;

    serverGUI app{storage, service};
    app.show();

    return QApplication::exec();
}
