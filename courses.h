#ifndef COURSES_H
#define COURSES_H

#include <QString>

class Courses
{
public:
    explicit Courses(const QString& name = "");

    int getId() const;
    void setId(int id);
    QString getName() const;
    void setName(const QString& name);

private:
    int m_id;
    QString m_name;
};

#endif // COURSES_H
