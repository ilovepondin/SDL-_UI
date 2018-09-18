#!/bin/bash
# ------------------------------------------------------------------------------
# name  2017.07.16 (xzhong)
# note
# ------------------------------------------------------------------------------
CPU=$1
TEMPLATE=$2
VENDOR=$3
PROJECT=$4
VERSION=$5

# ------------------------------------------------------------------------------
WORKDIR=$(cd "$(dirname "$0")"; pwd)
cd $WORKDIR

# ------------------------------------------------------------------------------
# add install extra files, ex. *.h *.sh ...etc
EXTRA_FILES="run.sh version"

# ------------------------------------------------------------------------------
# refresh run.sh
sed -i "/CPU=/c\CPU=${CPU}"                 run.sh
sed -i "/APP=/c\APP=${VENDOR}_${PROJECT}"   run.sh
sed -i "/VERSION=/c\VERSION=${VERSION}"     run.sh

# ------------------------------------------------------------------------------
# move old
OLD="../../.old/${PROJECT}"
[ -e $OLD ] || mkdir -p $OLD
mv -f ../*.tar $OLD
rm -r ../${PROJECT}_*

# ------------------------------------------------------------------------------
# install
INSTALL="../${PROJECT}_${VERSION}_${CPU}"
mkdir -p ${INSTALL}

cp -rp ./bin/${CPU}/* ${EXTRA_FILES} ${INSTALL}

# ------------------------------------------------------------------------------
# refresh install.sh
sed -i "/CPU=/c\CPU=${CPU}"                 install.sh
sed -i "/TEMPLATE=/c\TEMPLATE=${TEMPLATE}"  install.sh
sed -i "/VENDOR=/c\VENDOR=${VENDOR}"        install.sh
sed -i "/PROJECT=/c\PROJECT=${PROJECT}"     install.sh
sed -i "/VERSION=/c\VERSION=${VERSION}"     install.sh
cp -rp install.sh ${INSTALL}

tar -cf ../${PROJECT}_${VERSION}_${CPU}_install.tar ./${INSTALL}

# ------------------------------------------------------------------------------
# exec install.sh
./${INSTALL}/install.sh

# ------------------------------------------------------------------------------
# source
[ -e ./core ] && sudo rm core
tar -cf ../${PROJECT}_${VERSION}_source.tar ../${PROJECT}

# ------------------------------------------------------------------------------
# version
cp -rp version ../${PROJECT}_${VERSION}_version
