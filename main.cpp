#include "cihmappecrandyn.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CIhmAppEcranDyn w;
    w.show();

    return a.exec();
}
