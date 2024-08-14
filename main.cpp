#include "mwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mwin w;
    w.show();
    return a.exec();
}
