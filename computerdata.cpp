#include "computerdata.h"

ComputerData::ComputerData()
{

}

ComputerData::ComputerData(QString name, QString ip_addres, QString mac_addres)
{
    m_name = name;
    m_ip_addres = ip_addres;
    m_mac_addres = mac_addres;
}

QString ComputerData::getName() const
{
    return m_name;
}

void ComputerData::setName(const QString &value)
{
    m_name = value;
}

QString ComputerData::getIp() const
{
    return m_ip_addres;
}

void ComputerData::setIp(const QString &value)
{
    m_ip_addres = value;
}

QString ComputerData::getMac() const
{
    return m_mac_addres;
}

void ComputerData::setMac(const QString &value)
{
    m_mac_addres = value;
}
