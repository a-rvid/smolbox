CC?=gcc

CFLAGS += -std=c11 -Wall -Wextra -Oz                          \
	  -Isrc/lib/nolibc                                    \
	  -Isrc/lib/others                                    \
          -fcf-protection=none                                \
	  -fno-asm -nostdlib -ffreestanding                   \
	  -fno-ident -fno-asynchronous-unwind-tables          \
	  -fno-stack-protector                                \
	  -fno-unwind-tables -fmerge-all-constants            \
	  -ffunction-sections -fdata-sections

LDFLAGS = -flto                                \
          -Wl,-z,noseparate-code               \
          -Wl,-z,max-page-size=0x1000          \
          -Wl,--omagic                         \
          -Wl,--build-id=none                  \
          -Wl,--no-eh-frame-hdr                \
          -Wl,--gc-sections

OBJCOPY ?= objcopy

BIN=smolbox
BUILDDIR=build

$(shell rm -f src/lib/nolibc/hello.c)

SRCS := $(shell find src -name '*.c')
OBJS := $(patsubst src/%.c,$(BUILDDIR)/%.o,$(SRCS))

DESTDIR?=
PREFIX?=/usr/local
INSTALLDIR?=$(PREFIX)/bin

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -s -static -o $(BIN) $(LDFLAGS)
	$(OBJCOPY) --strip-section-headers $(BIN)

tiny: CFLAGS += -DSMOL_TINY
tiny: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -s -static -o $(BIN) $(LDFLAGS)
	$(OBJCOPY) --strip-section-headers $(BIN)

debug: CFLAGS += -ggdb
debug: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -static -o $(BIN) $(LDFLAGS)

$(BUILDDIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

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
	rm -rf $(BUILDDIR) $(BIN)

.PHONY: all tiny debug install clean build-deb clean-deb dev
