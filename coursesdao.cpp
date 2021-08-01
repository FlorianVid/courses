#include "coursesdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include "courses.h"

CoursesDao::CoursesDao(QSqlDatabase& database) :
    m_database(database)
{
}

void CoursesDao::init() const
{
    //m_database.open();
    if (!m_database.tables().contains("toutes_les_courses")) {
        QSqlQuery query(m_database);
        query.exec("CREATE TABLE toutes_les_courses (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    }
}

void CoursesDao::addCourses(Courses &courses) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO toutes_les_courses (name) VALUES (:name)");
    query.bindValue(":name", courses.getName());
    query.exec();
    courses.setId(query.lastInsertId().toInt());
}

QVector<Courses*> CoursesDao::getListCourses() const
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM toutes_les_courses");
    query.exec();
    QVector<Courses*> list;
    while(query.next()) {
        Courses* crs = new Courses();
        crs->setId(query.value("id").toInt());
        crs->setName(query.value("name").toString());
        list.append(crs);
    }
    return list;
}

void CoursesDao::updateCourses(const Courses& courses) const
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE toutes_les_courses SET (name) = (:name) WHERE (id) = (:id)");
    query.bindValue(":name", courses.getName());
    query.bindValue(":id", courses.getId());
    query.exec();
}

void CoursesDao::removeCourses(int id) const
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM toutes_les_courses WHERE (id) = (:id)");
    query.bindValue(":id", id);
    query.exec();
}

