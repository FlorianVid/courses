#include "alimentdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>
#include <QSqlDriver>
#include <QSqlError>
#include "aliment.h"

AlimentDao::AlimentDao(QSqlDatabase& database, QSqlDatabase& databaseSource) :
    m_database(database),
    m_databaseSource(databaseSource)
{
}

void AlimentDao::init() const
{
    if (!m_database.tables().contains("aliments")) {
        QSqlQuery query(m_database);
        query.exec("CREATE TABLE aliments (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, courses_id INTEGER)");
    }
}

void AlimentDao::addAlimentInCourses(Aliment &aliment, int coursesId) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO aliments (name, courses_id) VALUES (:name, :courses_id) ");
    query.bindValue(":name", aliment.getName());
    query.bindValue(":courses_id", coursesId);
    query.exec();
    aliment.setId(query.lastInsertId().toInt());
    aliment.setCoursesId(coursesId);

    //find in source database the associated nutriments
    //proteines
    QSqlQuery querySource(m_databaseSource);
    querySource.prepare("SELECT [Proteines (g)] FROM valeursNut WHERE Nom LIKE ?");
    querySource.bindValue(0, aliment.getName() + "%");

    if(!querySource.exec())
      qWarning() << "ERROR: " << querySource.lastError().text();

    querySource.first();//forced otherwise the rest does not work

    QString protStr = querySource.value(0).toString();
    protStr.replace(",",".");
    double protDouble = protStr.toDouble();

    //lipides
    querySource.prepare("SELECT [Lipides, totaux (g)] FROM valeursNut WHERE Nom LIKE ?");
    querySource.bindValue(0, aliment.getName() + "%");

    if(!querySource.exec())
      qWarning() << "ERROR: " << querySource.lastError().text();

    querySource.first();//forced otherwise the rest does not work

    QString lipStr = querySource.value(0).toString();
    lipStr.replace(",",".");
    double lipDouble = lipStr.toDouble();

    //glucides
    querySource.prepare("SELECT [Glucides, disponibles (g)] FROM valeursNut WHERE Nom LIKE ?");
    querySource.bindValue(0, aliment.getName() + "%");

    if(!querySource.exec())
      qWarning() << "ERROR: " << querySource.lastError().text();

    querySource.first();//forced otherwise the rest does not work

    QString glucideStr = querySource.value(0).toString();
    glucideStr.replace(",",".");
    double glucideDouble = glucideStr.toDouble();

    //Fibres
    querySource.prepare("SELECT [Fibres alimentaires (g)] FROM valeursNut WHERE Nom LIKE ?");
    querySource.bindValue(0, aliment.getName() + "%");

    if(!querySource.exec())
      qWarning() << "ERROR: " << querySource.lastError().text();

    querySource.first();//forced otherwise the rest does not work

    QString fibStr = querySource.value(0).toString();
    fibStr.replace(",",".");
    double fibDouble = fibStr.toDouble();

    aliment.setNut(protDouble, lipDouble, glucideDouble, fibDouble);

}

QVector<Aliment*> AlimentDao::getListAlimentsForCourses(int coursesId) const
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM aliments WHERE (courses_id) = (:courses_id)");
    query.bindValue(":courses_id", coursesId);
    query.exec();
    QVector<Aliment*> list;
    while(query.next()) {
        Aliment* alim = new Aliment();
        alim->setId(query.value("id").toInt());
        alim->setName(query.value("name").toString());
        alim->setCoursesId(coursesId);
        list.append(alim);
    }
    return list;
}

void AlimentDao::removeAliment(int id) const
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM aliments WHERE (id) = (:id)");
    query.bindValue(":id", id);
    query.exec();
}

void AlimentDao::removeAlimentFromCourses(int id, int coursesId) const
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM aliments WHERE (id) = (:id) AND (courses_id) = (:courses_id)");
    query.bindValue(":id", id);
    query.bindValue(":courses_id", coursesId);
    query.exec();
}

