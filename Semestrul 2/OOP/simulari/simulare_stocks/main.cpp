#include <QApplication>
#include <QPushButton>
#include "repository.h"
#include "service.h"
#include "StockGUI.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    string file_name = "storage.txt";
    RepoObject repo{file_name};
    repo.load_from_file();

    Service serv;
    StockGUI app{repo, serv};

    app.show();

    return QApplication::exec();
}
