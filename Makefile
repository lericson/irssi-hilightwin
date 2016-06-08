IRSSI_SOURCES := /usr/include/irssi/src
CFLAGS := -I$(IRSSI_SOURCES) \
          -I$(IRSSI_SOURCES)/core \
          -I$(IRSSI_SOURCES)/src/fe-common/core \
          $(shell pkg-config --cflags glib-2.0) \
          -fPIC
LDFLAGS := -shared -undefined dynamic_lookup \
           $(shell pkg-config --libs glib-2.0)


hilightwin.so: hilightwin.o
	$(LD) $(LDFLAGS) $< -o $@
