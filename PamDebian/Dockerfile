# PAM MODULE
# For Debian
#
#Version 1.0
#

FROM debian:latest
MAINTAINER Nicolas Constanty "nicolas.constanty@outlook.fr"

ENV DEBIAN_FRONTEND noninteractive

RUN echo "deb http://httpredir.debian.org/debian stretch main contrib non-free\ndeb-src http://httpredir.debian.org/debian stretch main contrib non-free\ndeb http://httpredir.debian.org/debian stretch-updates main contrib non-free\ndeb-src http://httpredir.debian.org/debian stretch-updates main contrib non-free\ndeb http://security.debian.org/ stretch/updates main contrib non-free\ndeb-src http://security.debian.org/ stretch/updates main contrib non-free" > /etc/apt/sources.list
RUN (apt-get update && apt-get upgrade -y -q && apt-get dist-upgrade -y -q && apt-get -y -q autoclean && apt-get -y -q autoremove)

RUN apt-get install -y -q openssl cryptsetup

ENV toto /home/toto
ENV titi /home/titi
ENV crypt /dev/zero
#ENV crypt /dev/urandom
#ENV crypt /dev/random

RUN useradd -m -d ${toto} -s /bin/bash -p $(echo toto | openssl passwd -1 -stdin) toto
RUN useradd -m -d ${titi} -s /bin/bash -p $(echo titi | openssl passwd -1 -stdin) titi


RUN (dd if=${crypt} of=${toto}/crypt_toto bs=1M count=256 && dd if=${crypt} of=${titi}/crypt_titi bs=1M count=256)
RUN (echo -n "toto" | cryptsetup -y luksFormat ${toto}/crypt_toto - && echo -n "titi" | cryptsetup -y luksFormat ${titi}/crypt_titi -)

RUN (chown toto:toto ${toto}/crypt_toto && chown titi:titi ${titi}/crypt_titi)
RUN echo "session optional			pam_automount.so" >> /etc/pam.d/common-session
RUN echo "auth optional             pam_automount.so  use_first_pass" >> /etc/pam.d/common-auth
RUN (cd && echo "ln -s /media/pam_modules/pam_automount.so /lib/x86_64-linux-gnu/security/pam_automount.so" >> .bashrc)
RUN (mv /sbin/cryptsetup /usr/bin/cryptsetup)
