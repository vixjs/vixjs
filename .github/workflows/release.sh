#!/bin/bash

set -ev

mkdir -p ${RELEASE_TAG}

DIST_DIRPATH="bin/${DIST_DIR}"
echo "DIST_DIRPATH is $DIST_DIRPATH"

if [[ $TARGET_OS_NAME == 'Linux' ]]; then # Linux
  VIXJS_FILE=${DIST_DIRPATH}/vixjs
  INSTALLER_FILE=${DIST_DIRPATH}/installer.sh
  XZ_FILE=${DIST_DIRPATH}/vixjs.xz
  GZ_FILE=${DIST_DIRPATH}/vixjs.tar.gz

  cp ${VIXJS_FILE} ${RELEASE_TAG}/vixjs-${RELEASE_TAG}-linux-${DIST_ARCH}
  cp ${INSTALLER_FILE} ${RELEASE_TAG}/installer-${RELEASE_TAG}-linux-${DIST_ARCH}.sh
  cp ${XZ_FILE} ${RELEASE_TAG}/vixjs-${RELEASE_TAG}-linux-${DIST_ARCH}.xz
  cp ${GZ_FILE} ${RELEASE_TAG}/vixjs-${RELEASE_TAG}-linux-${DIST_ARCH}.tar.gz

elif [[ $TARGET_OS_NAME == 'Darwin' ]]; then # Darwin
  VIXJS_FILE=${DIST_DIRPATH}/vixjs
  INSTALLER_FILE=${DIST_DIRPATH}/installer.sh
  XZ_FILE=${DIST_DIRPATH}/vixjs.xz
  GZ_FILE=${DIST_DIRPATH}/vixjs.tar.gz

  cp ${VIXJS_FILE} ${RELEASE_TAG}/vixjs-${RELEASE_TAG}-darwin-${DIST_ARCH}
  cp ${INSTALLER_FILE} ${RELEASE_TAG}/installer-${RELEASE_TAG}-darwin-${DIST_ARCH}.sh
  cp ${XZ_FILE} ${RELEASE_TAG}/vixjs-${RELEASE_TAG}-darwin-${DIST_ARCH}.xz
  cp ${GZ_FILE} ${RELEASE_TAG}/vixjs-${RELEASE_TAG}-darwin-${DIST_ARCH}.tar.gz

  if [[ $DIST_ARCH == 'x64' ]]; then
    echo "zip fullsrc..."
    # sudo sh build clean
    zip -r ./${RELEASE_TAG}/fullsrc.zip ./ -x *.git* -x out/* -x bin/* ${RELEASE_TAG} ${RELEASE_TAG}/*
  fi
fi

echo "list files in '${RELEASE_TAG}'";
ls -la ./${RELEASE_TAG};

exit 0;
