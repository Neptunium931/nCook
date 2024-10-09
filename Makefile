# Copyright (c) 2024, Tymothé BILLEREY <tymothe_billerey@fastmail.fr>
# See end of file for extended copyright information.

include config.mk

TARGET = nCook
TESTS = nCook_tests_Sqlite3

nCook_src = ./src/nCook.c \
						./src/sqlite/initSqlite.c \
						./src/sqlite/table.c
nCook_obj = $(nCook_src:.c=.c.o) 

CFLAGS += -I./test/
nCook_tests_Sqlite3_src = ./test/sqlite.c \
													./src/sqlite/initSqlite.c \
													./src/sqlite/table.c \
													./test/util/sqlite.c
nCook_tests_Sqlite3_obj = $(nCook_tests_Sqlite3_src:.c=.c.o)

nCook: $(nCook_obj)
	$(CC) -o $@ $(nCook_obj) $(LDFLAGS)

nCook_tests_Sqlite3: $(nCook_tests_Sqlite3_obj)
	$(CC) -o $@ $(nCook_tests_Sqlite3_obj) $(LDFLAGS)

%.c.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(nCook_obj) $(nCook_tests_Sqlite3_obj)
	rm -f $(TARGET)
	rm -f $(TESTS)

check: $(TESTS)
	for t in $(TESTS); do \
		sh -c "./$$t --tap"; \
	done

distcheck:

.PHONY: clean check distcheck

# This file is part of nCook
#
# BSD 3-Clause License
#
# Copyright (c) 2024, Tymothé BILLEREY <tymothe_billerey@fastmail.fr>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
