CC?=gcc


CFLAGS += -std=c11 -Wall -Wextra -Oz                         \
	 -pedantic-errors                                    \
         -I/usr/local/include                                \
         -fcf-protection=none                                \
	 -fno-asm -nostdlib -ffreestanding                   \
	 -fno-ident -fno-asynchronous-unwind-tables -DNDEBUG \
	 -fno-stack-protector

LDFLAGS = -s -static                  \
	  -L/usr/local/lib            \
          -Wl,-z,noseparate-code      \
          -Wl,-z,max-page-size=0x1000

LDLIBS = -llinux

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
	rm -rf packaging/debian/usr $(BIN)-x86_64.deb

clean:
	$(MAKE) clean-deb
	rm -f smolbox

.PHONY: install clean build-deb clean-deb
