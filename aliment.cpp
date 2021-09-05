#include "aliment.h"

Aliment::Aliment(const QString& name, double mass, const QString& category, double nbUnit) :
    m_name(name),
    m_mass(mass),
    m_category(category),
    m_nbUnit(nbUnit)
{
}

int Aliment::getId() const {
    return m_id;
}

void Aliment::setId(int id) {
    m_id = id;
}

void Aliment::setNut(double prot) {
    m_nut = {prot};
}

Nutriments Aliment::getNut() const {
    return m_nut;
}


QString Aliment::getName() const {
    return m_name;
}

QString Aliment::getCategory() const {
    return m_category;
}


double Aliment::getMass() const {
    return m_mass;
}

double Aliment::getNbUnit() const {
    return m_nbUnit;
}

void Aliment::setName(const QString& name) {
    m_name = name;
}

int Aliment::getCoursesId() const {
    return m_coursesId;
}

void Aliment::setCoursesId(int id) {
    m_coursesId = id;
}
