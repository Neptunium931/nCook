#include "initSqlite.h"
#include <stdlib.h>

const char *
getSqlitePath(void)
{
  const char *path = getenv("nCookDB");
  if (path == NULL || *path == '\0')
    path = "nCook.db";
  return path;
}
