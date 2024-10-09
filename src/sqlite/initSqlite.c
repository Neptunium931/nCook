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

char
initDataBase(void)
{
  int rc = sqlite3_open(getSqlitePath(), &db);
  if (rc == 0)
    return 0;
  return -1;
}

void
closeDataBase(void)
{
  sqlite3_close(db);
}
