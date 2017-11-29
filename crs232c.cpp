#include "crs232c.h"

CRs232c::CRs232c(QObject *parent, const QString &nomPort)
{
  qDebug() << nomPort;
  mSp = new QSerialPort(parent);
  mSp->setPortName(nomPort);
  connect(mSp, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

CRs232c::~CRs232c()
{
    mSp->close();
    delete mSp;
}

int CRs232c::initialiser(QSerialPort::BaudRate vitesse, QSerialPort::DataBits data,
                         QSerialPort::Parity parity, QSerialPort::StopBits nbStop,
                         QSerialPort::FlowControl flow)
{
    mSp->setBaudRate(vitesse);
    mSp->setDataBits(data);
    mSp->setParity(parity);
    mSp->setStopBits(nbStop);
    mSp->setFlowControl(flow);
    //mSp->setReadBufferSize(8);
    return 0;
}

int CRs232c::ouvrirPort()
{
    bool res=false;
    res=mSp->open(QIODevice::ReadWrite);
    if (!res) {
        qDebug() << "Erreur ouverture port.";
        mSp->close();
    } // if res
    return mSp->isOpen();
}

char CRs232c::lire(char *trame, int nbOctets, bool to)
{
    int res;
    if (nbOctets < 1) return ERREUR;

    if (to)
        res = mSp->waitForReadyRead(TO); // 3s d'attente max
    if (!res)
        return ERREUR;

    int nb = mSp->read(trame, nbOctets);
    qDebug() << nb << "cars lus";
    if (nb < nbOctets)
        return ERREUR;
    return OK;
}

char CRs232c::ecrire(char *trame, int nbOctets)
{
    int lg = mSp->write(trame, nbOctets);
    if ( lg < nbOctets) {
        qDebug() << "CRs232c::ecrire write KO...";
        return ERREUR;
    } // if erreur
    qDebug() << "Envoyé";
    return OK;
}

void CRs232c::onReadyRead()
{
    qDebug() << mSp->bytesAvailable() << "reçus.";
}
