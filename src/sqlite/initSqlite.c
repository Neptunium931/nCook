#include "initSqlite.h"
#include <stdlib.h>
static sqlite3 *db;

const char *
getSqlitePath(void)
{
  const char *path = getenv("nCookDB");
  if (path == NULL || *path == '\0')
    path = "nCook.db";
  return path;
}

void
initDataBase(void)
{
  sqlite3_open(getSqlitePath(), &db);
  if (db == NULL)
    exit(EXIT_FAILURE);
}

void
closeDataBase(void)
{
  sqlite3_close(db);
}
