// Copyright (c) 2024, Tymothé BILLEREY <tymothe_billerey@fastmail.fr>
// See end of file for extended copyright information.
#include "util/sqlite.h"
#include "sqlite/type.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern sqlite3 *db;

static bool ret = false;

static int
callbackIfExists(void *data, int argc, char **argv, char **azColName)
{
  ret = true;
  return 0;
}

bool
testIfTableExists(const char *name)
{
  char sql[BUFSIZ];
  sprintf(sql, "SELECT name FROM sqlite_master WHERE name = '%s'", name);
  int rc = sqlite3_exec(db, sql, callbackIfExists, NULL, NULL);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    return false;
  }
  return ret;
}

static enum ColumnType type = 0;
static int
callbackColumnType(void *data, int argc, char **argv, char **azColName)
{
  if (strcmp(argv[1], (char *)data) == 0)
  {
    if (strcmp(argv[2], "INTEGER") == 0)
    {
      type = INT;
    }
    else if (strcmp(argv[2], "TEXT") == 0)
    {
      type = TEXT;
    }
    else if (strcmp(argv[2], "BLOB") == 0)
    {
      type = BLOB;
    }
    if (atoi(argv[3]) == 1)
    {
      type |= NOTNULL;
    }
    else
    {
      type |= null;
    }
    if (atoi(argv[5]) == 1)
    {
      type |= PK;
    }
  }
  return 0;
}

enum ColumnType
getTypeOfColumn(const char *table, const char *column)
{
  char sql[BUFSIZ];
  sprintf(sql, "PRAGMA table_info('%s');", table);
  type = 0;
  int rc = sqlite3_exec(db, sql, callbackColumnType, (void *)column, NULL);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    return -1;
  }
  return type;
}
// This file is part of nCook
//
// BSD 3-Clause License
//
// Copyright (c) 2024, Tymothé BILLEREY <tymothe_billerey@fastmail.fr>
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
