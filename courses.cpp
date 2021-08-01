#include "courses.h"

Courses::Courses(const QString& name) : m_id(-1),
                                        m_name(name)
{
}

int Courses::getId() const {
    return m_id;
}

void Courses::setId(int id) {
    m_id = id;
}

QString Courses::getName() const {
    return m_name;
}

void Courses::setName(const QString& name) {
    m_name = name;
}
