#include "aliment.h"

Aliment::Aliment(const QString& name, double quantity, const QString& category) :
    m_name(name),
    m_quantity(quantity),
    m_category(category)
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


double Aliment::getQuantity() const {
    return m_quantity;
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
