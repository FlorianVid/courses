#ifndef ALIMENT_H
#define ALIMENT_H

#include <QString>

struct Nutriments {
    double protein;
};

class Aliment
{
public:
    Aliment(const QString& name = "");

    int getId() const;
    void setId(int id);
    QString getName() const;
    void setName(const QString& name);
    void setNut(double prot);
    Nutriments getNut() const;


    int getCoursesId() const;
    void setCoursesId(int idC);

private:
    int m_id;
    QString m_name;
    int m_coursesId;
    Nutriments m_nut;
};

#endif // ALIMENT_H
