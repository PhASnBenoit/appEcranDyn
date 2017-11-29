#ifndef CRS232C_H
#define CRS232C_H

#include <QSerialPort>
#include <QDebug>

#define ERREUR (char)-1
#define OK (char)0
#define TO 3000  // 3s timeout réception

class CRs232c : public QObject
{
    Q_OBJECT

public:
    explicit CRs232c(QObject *parent = 0, const QString &nomPort = "/dev/ttyUSB0");
    ~CRs232c();
    int initialiser(QSerialPort::BaudRate vitesse, QSerialPort::DataBits data,
                    QSerialPort::Parity parity, QSerialPort::StopBits nbStop,
                    QSerialPort::FlowControl flow);
    int ouvrirPort();
    char lire(char *trame, int nbOctets, bool to);
    char ecrire(char *trame, int nbOctets);

private:
    QSerialPort *mSp;

signals:

public slots:
    void onReadyRead();

};

#endif // CRS232C_H
