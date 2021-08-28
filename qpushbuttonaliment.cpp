#include "qpushbuttonaliment.h"

QPushButtonAliment::QPushButtonAliment(QString& name, QWidget *parent, QString cat, double mpu) :
    QPushButton(name, parent),
    m_category(cat),
    m_massPerUnit(mpu)
{

}

QString QPushButtonAliment::getCategory() const {
    return m_category;
}

double QPushButtonAliment::getMassPerUnit() const {
    return m_massPerUnit;
}
