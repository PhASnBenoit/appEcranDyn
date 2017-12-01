#ifndef CIHMAPPECRANDYN_H
#define CIHMAPPECRANDYN_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QMessageBox>
#include "ctelecommanders232samsung.h"

namespace Ui {
class CIhmAppEcranDyn;
}

class CIhmAppEcranDyn : public QMainWindow
{
    Q_OBJECT

public:
    explicit CIhmAppEcranDyn(QWidget *parent = 0);
    ~CIhmAppEcranDyn();

private slots:
    void on_pbAlimentation_clicked();
    void onErreurTc(char err, QString lieu);
    void on_pbSetSource_clicked();
    void on_pbGetSource_clicked();
    void on_pbActiver_clicked();
    void onAffTrame(QString trame);
    void on_pbEtat_clicked();
    void on_cbId_currentIndexChanged(int index);
    void onEtatAlimentation(char etat);
    void onSourceEntree(char src);

private:
    Ui::CIhmAppEcranDyn *ui;
    CTelecommandeRs232Samsung *tc;
    int mId;
};

#endif // CIHMAPPECRANDYN_H
