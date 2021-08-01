#ifndef ALIMENTDAO_H
#define ALIMENTDAO_H

#include <QVector>
class QSqlDatabase;
class Aliment;

class AlimentDao
{
public:
    explicit AlimentDao(QSqlDatabase& database, QSqlDatabase& databaseSource);
    void init() const;

    void addAlimentInCourses(Aliment& alim, int coursesId) const;
    void removeAlimentFromCourses(int id, int coursesId) const;
    void removeAliment(int id) const;
    QVector<Aliment*> getListAlimentsForCourses(int coursesId) const;

private:
    QSqlDatabase& m_database;
    QSqlDatabase& m_databaseSource;
};

#endif // COURSESDAO_H
