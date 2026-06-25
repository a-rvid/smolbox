CC?=gcc


CFLAGS += -std=c11 -Wall -Wextra -Oz                          \
	  -Ilib/linux/tools/include/nolibc                    \
          -fcf-protection=none -flto                          \
	  -fno-asm -nostdlib -ffreestanding                   \
	  -fno-ident -fno-asynchronous-unwind-tables          \
	  -fno-stack-protector

LDFLAGS = -Wl,-z,noseparate-code               \
          -Wl,-z,max-page-size=0x1000          \
          -Wl,--omagic

OBJCOPY ?= objcopy

BIN=smolbox

DESTDIR?=
PREFIX?=/usr/local
INSTALLDIR?=$(PREFIX)/bin

all:
	$(CC) $(CFLAGS) src/main.c -s -static -o $(BIN) $(LDFLAGS)
	$(OBJCOPY) --strip-section-headers $(BIN)

debug:
	$(CC) $(CFLAGS) src/main.c -ggdb -static -o $(BIN) $(LDFLAGS)

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

.PHONY: install clean build-deb clean-deb dev
