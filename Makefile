# Copyright (c) 2024, Tymothé BILLEREY <tymothe_billerey@fastmail.fr>
# See end of file for extended copyright information.

include config.mk

TARGET = nCook
TESTS = nCook_tests_Sqlite3

nCook_src = ./src/nCook.c \
						./src/sqlite/initSqlite.c \
						./src/sqlite/initSqlite.h \
						./src/sqlite/table.c \
						./src/sqlite/table.h \
						./src/sqlite/type.h

nCook_obj = $(nCook_src:.c=.c.o) 

CFLAGS += -I./test/
CFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address
nCook_tests_Sqlite3_src = ./test/sqlite.c \
													./src/sqlite/initSqlite.c \
													./src/sqlite/initSqlite.h \
													./src/sqlite/table.c \
													./src/sqlite/table.h \
													./test/util/sqlite.c \
													./test/util/sqlite.h \
													./src/sqlite/type.h

ifdef CODECOV
	CFLAGS += ${codecov_FLAGS}
	LDFLAGS += ${codecov_FLAGS}
endif

nCook_tests_Sqlite3_obj = $(nCook_tests_Sqlite3_src:.c=.c.o)

nCook: $(nCook_obj)
	$(CC) -o $@ $(nCook_obj) $(LDFLAGS)

nCook_tests_Sqlite3: $(nCook_tests_Sqlite3_obj)
	$(CC) -o $@ $(nCook_tests_Sqlite3_obj) $(LDFLAGS) $(criterion_LDFLAGS)

%.c.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
	rm -f $(TESTS)
	find . -name "*.gcda" -exec rm -f {} \;
	find . -name "*.gcno" -exec rm -f {} \;
	find . -name "*.c.o" -exec rm -f {} \;
	rm -f tags

tags:
	ctags -R .

check: $(TESTS)
	for t in $(TESTS); do \
		sh -c "./$$t --tap"; \
		done

distcheck:

dist:
	tar cvf $(TARGET).tar $(nCook_src) $(nCook_tests_Sqlite3_src) Makefile config.mk LICENSE

dist-gzip: dist
	gzip $(TARGET).tar

dist-bzip2: dist
	bzip2 $(TARGET).tar

dist-xz: dist
	xz $(TARGET).tar

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
