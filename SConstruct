#!/usr/bin/env python
env = Environment(CCFLAGS="-fPIC", CPPDEFINES="-DHAVE_CONFIG_H")
env.ParseConfig('pkg-config --libs --cflags glib-2.0')
env.ParseConfig('./irssi-source.sh')
env.SharedLibrary(
    'hilightwin',
    [env.SharedObject("hilightwin.c")],
    #[env.SharedObject("hilightwin.c"),
    # env.SharedObject("module-formats.c")],
    CPPATH=".",
    LINKFLAGS="-undefined dynamic_lookup",
    LIBS=["glib-2.0"],
)

# vim: ft=python ts=4 et :
