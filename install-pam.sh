#!/usr/bin/env bash

echo "deb http://httpredir.debian.org/debian stretch main contrib non-free\ndeb-src http://httpredir.debian.org/debian stretch main contrib non-free\ndeb http://httpredir.debian.org/debian stretch-updates main contrib non-free\ndeb-src http://httpredir.debian.org/debian stretch-updates main contrib non-free\ndeb http://security.debian.org/ stretch/updates main contrib non-free\ndeb-src http://security.debian.org/ stretch/updates main contrib non-free" > /etc/apt/sources.list

apt-get update && apt-get upgrade -y -q && apt-get dist-upgrade -y -q && apt-get -y -q autoclean && apt-get -y -q autoremove

apt-get install -y -q openssl cryptsetup

apt-get install -y -q git

apt-get install -y -q g++

apt-get install -y -q nano

apt-get install -y -q make

apt-get install -y -q libcryptsetup-dev

apt-get install -y -q libpam-dev

apt-get install -y -q autoconf

apt-get install -y -q automake

apt-get install -y -q libtool

apt-get install -y -q libboost-dev


git clone https://github.com/Nicolas-Constanty/Module-pam-automount.git

cd Module-pam-automount

./configure

make

make install

exit