#ifndef COURSESDAO_H
#define COURSESDAO_H

#include <QVector>
class QSqlDatabase;
class Courses;

class CoursesDao
{
public:
    explicit CoursesDao(QSqlDatabase& database);
    void init() const;
    void addCourses(Courses& courses) const;
    void updateCourses(const Courses& courses) const;
    void removeCourses(int id) const;
    QVector<Courses*> getListCourses() const;

private:
    QSqlDatabase& m_database;
};

#endif // COURSESDAO_H
