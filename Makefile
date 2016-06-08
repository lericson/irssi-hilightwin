IRSSI_SOURCES ?= /usr/include/irssi/src
CFLAGS := -I$(IRSSI_SOURCES) \
          -I$(IRSSI_SOURCES)/core \
          -I$(IRSSI_SOURCES)/src/fe-common/core \
          -fPIC \
          $(shell pkg-config --cflags glib-2.0)
LDFLAGS := -shared \
           -undefined dynamic_lookup \
           $(shell pkg-config --libs glib-2.0)

libhilightwin.so: hilightwin.o
	$(LD) $(LDFLAGS) $< -o $@
