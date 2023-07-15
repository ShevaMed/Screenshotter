#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <src/screenlogic/screenshotinfo.h>

#include <QSqlDatabase>

class DBManager
{
public:
    static DBManager& instance();
    QSqlDatabase& getDatabase();

private:
    DBManager();
    ~DBManager();

    DBManager(const DBManager&) = delete;
    void operator=(const DBManager&) = delete;

public:
    bool openDB();

    bool execute(QSqlQuery& query) const;
    bool insertScreenshot(const ScreenshotInfo& sreenshot) const;
    QVector<ScreenshotInfo> selectAllScreenshots() const;

private:
    QSqlDatabase database_;
};

#endif // DBMANAGER_H
