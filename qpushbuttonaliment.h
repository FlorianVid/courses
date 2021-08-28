#ifndef QPUSHBUTTONALIMENT_H
#define QPUSHBUTTONALIMENT_H

#include <QPushButton>

class QPushButtonAliment : public QPushButton
{
public:
    QPushButtonAliment(QString& name, QWidget *parent = nullptr, QString cat = "", double mpu = 0);
    QString getCategory() const;
    double getMassPerUnit() const;
private:
    QString m_category;
    double m_massPerUnit;
};

#endif // QPUSHBUTTONALIMENT_H
