#ifndef COMPUTERDATA_H
#define COMPUTERDATA_H

#include <QString>

//  Имя компьютера, IP адрес, MAC адрес.

class ComputerData
{
public:
    ComputerData();
    ComputerData(QString name, QString ip_addres, QString mac_addres);

    QString getName() const;
    void setName(const QString &value);

    QString getIp() const;
    void setIp(const QString &value);

    QString getMac() const;
    void setMac(const QString &value);


private:
    QString m_name;
    QString m_ip_addres;
    QString m_mac_addres;
};

#endif // COMPUTERDATA_H
