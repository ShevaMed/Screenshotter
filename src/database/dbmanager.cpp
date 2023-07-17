#include "dbmanager.h"
#include "src/screenlogic/screenshotinfo.h"

#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QVariant>

DBManager &DBManager::instance()
{
    static DBManager instance;
    return instance;
}

QSqlDatabase &DBManager::getDatabase()
{
    return database_;
}

DBManager::DBManager()
{
    database_ = QSqlDatabase::addDatabase("QSQLITE");
    database_.setConnectOptions("QSQLITE_ENABLE_REGEXP");
    database_.setDatabaseName(QCoreApplication::applicationDirPath() + "/screens.db");
}

bool DBManager::openDB()
{
    if (!database_.open()) {
        QMessageBox::critical(nullptr, "Error opening database",
                              "Could not open database. Please try again!\n"
                              + database_.lastError().databaseText());
        return false;
    }

    if (database_.tables().isEmpty()) {
        QSqlQuery query(database_);
        query.prepare("CREATE TABLE `screenshots` ("
                      "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                      "`hash` INTEGER NOT NULL,"
                      "`similarity` INTEGER NOT NULL,"
                      "`data` BLOB NOT NULL"
                      ");");
        return this->execute(query);
    }
    return true;
}

bool DBManager::execute(QSqlQuery &query) const
{
    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database query error",
                              "Failed to access the database."
                              "Try again!\n" + query.lastError().text());
        return false;
    }
    return true;
}

bool DBManager::insertScreenshot(const ScreenshotInfo &sreenshot) const
{
    QSqlQuery query(database_);
    query.prepare("INSERT INTO screenshots(hash, similarity, data) "
                  "VALUES(:hash, :similarity, :data)");
    query.bindValue(":hash", sreenshot.hash);
    query.bindValue(":similarity", sreenshot.similarity);
    query.bindValue(":data", sreenshot.data);
    return this->execute(query);
}

QVector<ScreenshotInfo> DBManager::selectAllScreenshots() const
{
    QSqlQuery query(database_);
    query.prepare("SELECT hash, similarity, data FROM screenshots");
    query.setForwardOnly(true);

    QVector<ScreenshotInfo> screens;

    if (this->execute(query)) {
        while (query.next()) {
            qint64 hash = query.value("hash").toLongLong();
            qint16 similarity = static_cast<qint16>(query.value("similarity").toInt());
            QByteArray data = query.value("data").toByteArray();

            screens.push_back(ScreenshotInfo(hash, similarity, data));
        }
    }
    return screens;
}

DBManager::~DBManager()
{
    if (database_.isOpen()) {
        database_.close();
    }
}
