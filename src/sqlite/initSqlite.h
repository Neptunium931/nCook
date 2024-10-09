#ifndef _initSqlite_h
#define _initSqlite_h
#include <sqlite3.h>

const char *getSqlitePath(void);

char initDataBase(void);
void closeDataBase(void);

#endif // !_initSqlite_h
