#!/bin/bash
# ------------------------------------------------------------------------------
# name  2017.07.16 (xzhong)
# note
# ------------------------------------------------------------------------------
CPU=x86
APP=auo_ariel
VERSION=0.0.02_20180126_XZ

printf "[%12s] %s\n" "$(cat /proc/uptime | cut -d' ' -f 1)" "${APP}_${VERSION}" > /dev/console

ulimit -c unlimited
sysctl -p > /dev/null 2>&1

WORKDIR=$(cd "$(dirname "$0")"; pwd)
cd $WORKDIR

export PATH=./:./bin/$CPU:$PATH

export LD_LIBRARY_PATH=/usr/lib/auo/$CPU:$LD_LIBRARY_PATH

$APP $*
