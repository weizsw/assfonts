#!/bin/bash

BUILD_TYPE=Release

INSTALL_PREFIX=$(realpath -m install)

while getopts "b:o:" arg
do
    case $arg in
        b)
            BUILD_TYPE=$OPTARG
            ;;
        o)
            INSTALL_PREFIX=$(realpath -m $OPTARG)
            ;;
        ?)
    exit 1
    ;;
    esac
done

conan profile detect -vquiet

if (( $EUID != 0 ))
then        
    conan install . -b missing -s build_type=${BUILD_TYPE} -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
else
    conan install . -b missing -s build_type=${BUILD_TYPE} -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=False
fi

cd build
source conanbuild.sh
cmake .. --preset conan-${BUILD_TYPE,,}
cmake --build --preset conan-${BUILD_TYPE,,} -j
cmake --install ${BUILD_TYPE} --prefix ${INSTALL_PREFIX} --strip