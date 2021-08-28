#ifndef ALIMENT_H
#define ALIMENT_H

#include <QString>

struct Nutriments {
    double protein;
};

class Aliment
{
public:
    Aliment(const QString& name = "", double quantity = 0, const QString& category = "");

    int getId() const;
    void setId(int id);
    QString getName() const;
    void setName(const QString& name);
    void setNut(double prot);
    Nutriments getNut() const;


    int getCoursesId() const;
    void setCoursesId(int idC);
    QString getCategory() const;
    double getQuantity() const;

private:
    int m_id;
    QString m_name;
    int m_coursesId;
    Nutriments m_nut;
    double m_quantity; //in kg
    QString m_category; //legume, fruit or viande
};

#endif // ALIMENT_H
