#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include "coursesdao.h"
#include "alimentdao.h"

class QSqlDatabase;

const QString DATABASE_FILENAME = "C:\\Users\\fvida\\Documents\\codeQt\\raggamuffin\\data\\history.db";
const QString DATABASE_SOURCE_FILENAME = "C:\\Users\\fvida\\Documents\\codeQt\\raggamuffin\\data\\valeursNut.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME, const QString& pathSource = DATABASE_SOURCE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);
private:
    QSqlDatabase* m_database;
    QSqlDatabase* m_databaseSource;
public:
    const CoursesDao m_coursesDao;
    const AlimentDao m_alimentDao;

};

#endif // DATABASEMANAGER_H
