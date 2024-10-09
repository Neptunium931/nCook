#include "sqlite/initSqlite.h"
#include <criterion/criterion.h>
#include <stdio.h>
#include <unistd.h>

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

bool testIfFileExists(const char *path);
bool
testIfFileExists(const char *path)
{
  return access(path, F_OK) == 0;
}

void removeDataBase(void);
void
removeDataBase(void)
{
  remove(getSqlitePath());
}

Test(sqlite, initSqlite, .fini = removeDataBase)
{
  initDataBase();
  cr_assert(testIfFileExists(getSqlitePath()));
  closeDataBase();
}

Test(sqlite, initDBPathNotExist)
{
  setenv("nCookDB", "./tmp/nCook.db", 1);
  cr_assert_eq(initDataBase(), -1);
  closeDataBase();
}
