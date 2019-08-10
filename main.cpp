#include <QtWidgets>
#include <QApplication>
#include "classmaker_cpp.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    ClassMaker_cpp window;
    window.show();

    return app.exec();

}
