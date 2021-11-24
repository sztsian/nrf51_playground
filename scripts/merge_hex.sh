#!/bin/bash

SD_HEX=$1
APP_HEX=$2
FULL_HEX=$3

if [ $# -le 2 ] ; then
    echo 'Usage: merge_hex.sh ${PATH_TO_SD} ${PATH_TO_APP} ${PATH_TO_FULL}'
    exit -1
fi

echo 'Merging ihex files...'

# Copy SoftDevice file
cat "${SD_HEX}" > "${FULL_HEX}"

# Strip the last line (EOF marker) from SoftDevice.
sed -i "$ d" "${FULL_HEX}"

# Append application code to the file
cat "${APP_HEX}" >> "${FULL_HEX}"

echo 'Done.'