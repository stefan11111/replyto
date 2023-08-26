PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man

all: replyto.c replyto.h
	$(CC) -o replyto replyto.c

install: replyto
	mkdir -p $(DESTDIR)$(BINDIR)
	cp -f replyto $(DESTDIR)$(BINDIR)
	chmod 755 $(DESTDIR)$(BINDIR)/replyto

clean:
	rm -f replyto

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/replyto

.PHONY: all install uninstall clean
