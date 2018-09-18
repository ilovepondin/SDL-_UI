#!/bin/bash
# ------------------------------------------------------------------------------
# name      2017.07.16 (xzhong)
# note
# 20170725  add cross complie on x86
# ------------------------------------------------------------------------------
CPU=x86
TEMPLATE=app
VENDOR=auo
PROJECT=ariel
VERSION=0.0.02_20180126_XZ

# ------------------------------------------------------------------------------
WORKDIR=$(cd "$(dirname "$0")"; pwd)
cd $WORKDIR


# ------------------------------------------------------------------------------
ARM=`uname -a | grep arm`
X86=`uname -a | grep x86`

if [ "$ARM" -a $CPU == "arm" ] || [ "$X86" -a $CPU == "x86" ]; then

    if [ $TEMPLATE == "lib" ]; then

        [ -e /usr/lib/$VENDOR/$CPU ] || mkdir -p /usr/lib/$VENDOR/$CPU
        rm -f /usr/lib/$VENDOR/$CPU/lib${VENDOR}_${PROJECT}.so*
        cp *.so* /usr/lib/$VENDOR/$CPU

        [ -e /usr/include/$VENDOR ] || mkdir -p /usr/include/$VENDOR
        cp *.h  /usr/include/$VENDOR

    else # app

        [ -e /home/$VENDOR/$PROJECT ] || mkdir -p /home/$VENDOR/$PROJECT

        pkill $VENDOR_$PROJECT

        rm -rf /home/$VENDOR/$PROJECT/*
        rsync -rv --exclude=install.sh * /home/$VENDOR/$PROJECT

    fi

elif [ "$X86" -a $CPU == "arm" ]; then   #for cross compile on x86

    if [ $TEMPLATE == "lib" ]; then

        [ -e /usr/lib/$VENDOR/$CPU ] || mkdir -p /usr/lib/$VENDOR/$CPU
        rm -f /usr/lib/$VENDOR/$CPU/lib${VENDOR}_${PROJECT}.so*
        cp *.so* /usr/lib/$VENDOR/$CPU

        [ -e $SDKTARGETSYSROOT/usr/include/$VENDOR ] || mkdir -p $SDKTARGETSYSROOT/usr/include/$VENDOR
        cp *.h  $SDKTARGETSYSROOT/usr/include/$VENDOR

    fi
fi

