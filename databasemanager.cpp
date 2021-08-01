#include "databasemanager.h"

#include <QSqlDatabase>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString& path, const QString& pathSource) :
    m_database(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    m_databaseSource(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    m_coursesDao(*m_database),
    m_alimentDao(*m_database, *m_databaseSource)
{
    m_database->setDatabaseName(path);
    m_database->open();

    m_databaseSource->setDatabaseName(pathSource);
    m_databaseSource->setConnectOptions("QSQLITE_OPEN_READONLY");
    m_databaseSource->open();

    m_coursesDao.init();
    m_alimentDao.init();
}

DatabaseManager::~DatabaseManager()
{
    m_database->close();
    delete  m_database;
    delete  m_databaseSource;
}
