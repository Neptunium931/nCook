// Copyright (c) 2024, Tymothé BILLEREY <tymothe_billerey@fastmail.fr>
// See end of file for extended copyright information.
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
