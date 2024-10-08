#include "sqlite/initSqlite.h"
#include <criterion/criterion.h>

Test(sqlite, pathDefault)
{
  const char *path = getSqlitePath();
  cr_assert_str_eq(path, "nCook.db");
}

Test(sqlite, pathCustom)
{
  setenv("nCookDB", "test.db", 1);
  const char *path = getSqlitePath();
  cr_assert_str_eq(path, "test.db");
}

Test(sqlite, pathCustomEmpty)
{
  setenv("nCookDB", "", 1);
  const char *path = getSqlitePath();
  cr_assert_str_eq(path, "nCook.db");
}

Test(sqlite, initSqlite) {}
