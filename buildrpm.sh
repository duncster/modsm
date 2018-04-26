#!/bin/bash
rm -rf rpmbuild
mkdir -p rpmbuild/SPECS
mkdir -p rpmbuild/SOURCES

cp modsm.spec rpmbuild/SPECS

mkdir modsm-1.0
cp ./modsm.c modsm-1.0/
cp ./Makefile modsm-1.0/
tar cvf - modsm-1.0/ | gzip -9c >rpmbuild/SOURCES/modsm-1.0-1.tar.gz
rm -rf modsm-1.0/

rpmbuild -bb rpmbuild/SPECS/modsm.spec --define "_topdir $PWD/rpmbuild"
