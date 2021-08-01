#include "aliment.h"

Aliment::Aliment(const QString& name) : m_name(name)
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

void Aliment::setName(const QString& name) {
    m_name = name;
}

int Aliment::getCoursesId() const {
    return m_coursesId;
}

void Aliment::setCoursesId(int id) {
    m_coursesId = id;
}
