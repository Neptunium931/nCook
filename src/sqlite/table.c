// Copyright (c) 2024, Tymothé BILLEREY <tymothe_billerey@fastmail.fr>
// See end of file for extended copyright information.
#include "table.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern sqlite3 *db;

char
createTable(const char *name, unsigned int size, Column *c)
{
  char sql[BUFSIZ];
  sprintf(sql, "CREATE TABLE IF NOT EXISTS %s (", name);
  for (unsigned int i = 0; i < size; i++)
  {
    sprintf(sql + strlen(sql), "%s ", c[i].name);
    if (c[i].type & INT)
      sprintf(sql + strlen(sql), "INTEGER ");
    if (c[i].type & TEXT)
      sprintf(sql + strlen(sql), "TEXT ");
    if (c[i].type & BLOB)
      sprintf(sql + strlen(sql), "BLOB ");
    if (c[i].type & PK)
      sprintf(sql + strlen(sql), "PRIMARY KEY ");
    if (c[i].type & null)
      sprintf(sql + strlen(sql), "NULL ");
    if (c[i].type & NOTNULL)
      sprintf(sql + strlen(sql), "NOT NULL ");
    if (c[i].type & UNIQUE)
      sprintf(sql + strlen(sql), "UNIQUE ");
    if (i < size - 1)
      sprintf(sql + strlen(sql), ", ");
  }

  sprintf(sql + strlen(sql), ");");

  int rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  return 0;
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
