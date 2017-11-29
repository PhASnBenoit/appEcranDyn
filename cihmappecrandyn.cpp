#include "cihmappecrandyn.h"
#include "ui_cihmappecrandyn.h"

CIhmAppEcranDyn::CIhmAppEcranDyn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppEcranDyn)
{
    ui->setupUi(this);
    //ui->pbStart->setEnabled(false);
    ui->gbEcran->setEnabled(false);

    tc = NULL;

    QList<QSerialPortInfo> lps;
    lps = QSerialPortInfo::availablePorts();
    for(int i=0 ; i<lps.size() ; i++) {
        ui->cbPorts->addItem(lps.at(i).portName());
    } // for port série

    for(int i=0 ; i<255 ; i++)
        ui->cbId->addItem(QString::number(i));
    ui->cbId->setCurrentIndex(1);

    ui->cbSource->addItem("PC");
    ui->cbSource->addItem("DVI");
    ui->cbSource->addItem("SOURCE_IN");
    ui->cbSource->addItem("COMPOSANT");
    ui->cbSource->addItem("MAGIC_INFO");
    ui->cbSource->addItem("DVI_VIDEO");
    ui->cbSource->addItem("HDMI1");
    ui->cbSource->addItem("HDMI_PC");
    ui->cbSource->addItem("HDMI2");
    ui->cbSource->addItem("HDMI2_PC");
    ui->cbSource->addItem("HDBT");
}

CIhmAppEcranDyn::~CIhmAppEcranDyn()
{
    if (tc) delete tc;
    delete ui;
}

void CIhmAppEcranDyn::on_pbAlimentation_clicked()
{
    if (ui->pbAlimentation->text() == "Allumer") {
        ui->pbAlimentation->setText("Eteindre");
        tc->setAlimentation(ui->cbId->currentText().toInt(), true);
    } else {
        ui->pbAlimentation->setText("Allumer");
        tc->setAlimentation(ui->cbId->currentText().toInt(), false);
    } // else
}

void CIhmAppEcranDyn::onErreurTc(char err, QString lieu)
{
    QMessageBox::warning(this, "Erreur", "Erreur "+QString::number(err,10)+" "+lieu);
}

void CIhmAppEcranDyn::on_pbActiver_clicked()
{
  if (ui->pbActiver->text() == "Activer") {
    ui->pbActiver->setText("Désactiver");
    QString port("/dev/"+ui->cbPorts->currentText());
    if (tc) delete tc;
    tc = new CTelecommandeRs232Samsung(this, port.toStdString().c_str());
    connect(tc, SIGNAL(sigErreur(char, QString)), this, SLOT(onErreurTc(char, QString)));
    connect(tc, SIGNAL(sigAffTrame(QString)), this, SLOT(onAffTrame(QString)));
    ui->gbEcran->setEnabled(true);
    ui->cbPorts->setEnabled(false);
    onAffTrame("Port ouvert.");
  } else {
    ui->pbActiver->setText("Activer");
    delete(tc);
    tc=NULL;
    ui->gbEcran->setEnabled(false);
    ui->cbPorts->setEnabled(true);
    onAffTrame("Port fermé.");
  } // else
}

void CIhmAppEcranDyn::onAffTrame(QString trame)
{
    ui->lTrame->setText(trame);
}

void CIhmAppEcranDyn::on_pbEtat_clicked()
{
    char etat = tc->getEtatAlimentation(mId);
    if (etat==1)
        ui->lEtat->setText("Allumé");
    else
        ui->lEtat->setText("Eteint");
}

void CIhmAppEcranDyn::on_cbId_currentIndexChanged(int index)
{
    mId = index;
}

void CIhmAppEcranDyn::on_pbSetSource_clicked()
{
  tc->setSourceEntree(mId, tc->getCodeSource(ui->cbSource->currentText()));
}

void CIhmAppEcranDyn::on_pbGetSource_clicked()
{
    int source=tc->getSourceEntree(mId);
    QString ssource;
    ssource = tc->getSource((E_SOURCE_ENTREE)source);
    ui->lGetSource->setText(ssource);
}
