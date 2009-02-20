#!/bin/sh
IRSSI_P="irssi"
IRSSI_V="0.8.12"
IRSSI_PN="${IRSSI_P}-${IRSSI_V}"
IRSSI_HTTP="http://irssi.org/files/"

if [ ! -d "${IRSSI_PN}" ]; then
    IRSSI_AR="${IRSSI_PN}.tar.bz2"
    (   ([ ! -f "${IRSSI_AR}" ] && wget -q "${IRSSI_HTTP}${IRSSI_AR}") && \
        tar -xjf "${IRSSI_AR}" && \
        (cd "${IRSSI_PN}" && ./configure --without-perl 1>/dev/null 2>&1) && \
        rm -f "${IRSSI_AR}") \
    || exit
fi

echo "-I${IRSSI_PN}/" "-I${IRSSI_PN}/src/" "-I${IRSSI_PN}/src/core/" \
     "-I${IRSSI_PN}/src/fe-common/core/"
