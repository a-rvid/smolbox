CC?=gcc
STD?=-std=c23
CFLAGS += -Wall -Oz -s -fno-ident -fno-asynchronous-unwind-tables -DNDEBUG $(STD)

BIN=smolbox

DESTDIR?=
PREFIX?=/usr/local
INSTALLDIR?=$(PREFIX)/bin

smolbox:
	$(CC) $(CFLAGS) src/main.c -o $(BIN)

install:
	mkdir -p $(DESTDIR)$(INSTALLDIR)
	install -m 555 $(BIN) $(DESTDIR)$(INSTALLDIR)/$(BIN)

build-deb:
	PREFIX=/usr DESTDIR=packaging/debian $(MAKE) install
	dpkg-deb --root-owner-group --build packaging/debian
	mv packaging/debian.deb ./$(BIN)-x86_64.deb

clean-deb:
	rm -rf packaging/debian/usr sanctum-x86_64.deb

clean:
	$(MAKE) clean-deb
	rm -f smolbox

.PHONY: install clean build-deb clean-deb
