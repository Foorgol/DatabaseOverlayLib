/* 
 * File:   GenericDatabase.h
 * Author: volker
 *
 * Created on February 2, 2014, 9:52 AM
 */

#ifndef GENERICDATABASE_H
#define	GENERICDATABASE_H

#include <string>
#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QList>
#include <QVariant>

#include "Logger.h"

using namespace std;

namespace dbOverlay
{

  class GenericDatabase : public QObject
  {

    Q_OBJECT

  public:
    /**
     * An enum to identify the database type for the connection
     */
    enum DB_ENGINE
    {
      SQLITE,
      MYSQL
    };


    GenericDatabase ();
    GenericDatabase(QString sqliteFileName, bool createNew);
    GenericDatabase(DB_ENGINE t, QString srv, int port, QString name, QString user, QString pw);
    
    virtual ~GenericDatabase ();
    
    int execNonQuery(const QString& baseSqlStatement, const QVariantList& params);
    int execNonQuery(const QString& baseSqlStatement);
    void enforceSynchronousWrites(bool syncOn);
    
    virtual void populateTables() = 0;
    virtual void populateViews() = 0;
    
    void tableCreationHelper(const QString& tabName, const QList<QString>& colDefs);
    void viewCreationHelper(const QString& viewName, const QString& selectStmt);
    
    
  private:
    void dumpError(QSqlQuery *qry, bool throwException = false);
    void dumpSuccessInfo(QSqlQuery *qry, int result);
    static int connectionCounter;
    QString internalConnectionName;

  protected:
    const int MYSQL_DEFAULT_PORT = 3306;

    /**
     * A logger for error messages
     */
    Logger *log;

    /**
     * The connection object for the database handled by this class
     */
    QSqlDatabase conn;

    /**
     * The user name for the database server
     */
    QString dbUser;

    /**
     * The password for the database server
     */
    QString dbPasswd;

    /**
     * The name of the database to be accessed
     */
    QString dbName;

    /**
     * The database type for the connection
     */
    DB_ENGINE dbType;

    /**
     * The name of the server to connect to
     */
    QString dbServer;

    /**
     * The server port to connect to
     */
    int dbPort;

    /**
     * A counter for executed queries; for debugging purposes only
     */
    long queryCounter = 0;

    const int FAKED_PORT_NUM_FOR_CREATING_NEW_SQLITE_FILE = -100;
    const int FAKED_PORT_NUM_FOR_OPENING_EXISTING_SQLITE_FILE = -200;
    
    void initDB(DB_ENGINE t, QString srv, int port, QString name, QString user, QString pw);
    
    QSqlQuery* prepStatement(const QString& baseSqlStatement, const QVariantList& params);

  };
}
#endif	/* GENERICDATABASE_H */
