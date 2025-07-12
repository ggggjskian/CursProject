#include <QApplication>
#include<QIcon>
#include "..\modules\GUI\main_window.hpp"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/app_icon.png"));
    MainWindow window;
    window.show();
    return app.exec();
}