#!/bin/sh

set -e

IRSSI_P="irssi"
IRSSI_V="0.8.19"
IRSSI_PN="${IRSSI_P}-${IRSSI_V}"
IRSSI_HTTP="https://github.com/irssi/irssi/releases/download/"

if [ ! -d "${IRSSI_PN}" ]; then
    IRSSI_AR="${IRSSI_PN}.tar.gz"
    [ ! -f "${IRSSI_AR}" ] && wget "${IRSSI_HTTP}${IRSSI_V}/${IRSSI_AR}"
    tar -xzf "${IRSSI_AR}"
    (cd "${IRSSI_PN}" && ./configure --without-perl 1>/dev/null 2>&1)
    rm -f "${IRSSI_AR}"
fi

echo "Run the following to compile:"
echo "  make IRSSI_SOURCES=${IRSSI_PN}/src"
