# PAM MODULE
# For Debian
#
#Version 1.0
#

FROM debian:latest
MAINTAINER Nicolas Constanty "nicolas.constanty@outlook.fr"

ENV DEBIAN_FRONTEND noninteractive

RUN echo "deb http://httpredir.debian.org/debian jessie main contrib non-free\ndeb-src http://httpredir.debian.org/debian jessie main contrib non-free\ndeb http://httpredir.debian.org/debian jessie-updates main contrib non-free\ndeb-src http://httpredir.debian.org/debian jessie-updates main contrib non-free\ndeb http://security.debian.org/ jessie/updates main contrib non-free\ndeb-src http://security.debian.org/ jessie/updates main contrib non-free" > /etc/apt/sources.list
RUN (apt-get update && apt-get upgrade -y -q && apt-get dist-upgrade -y -q && apt-get -y -q autoclean && apt-get -y -q autoremove)


RUN apt-get install -y -q openssl
RUN useradd -m -d /home/toto  -s /bin/bash -p $(echo toto | openssl passwd -1 -stdin) toto
RUN useradd -m -d /home/titi  -s /bin/bash -p $(echo titi | openssl passwd -1 -stdin) titi
RUN echo "session required			pam_test.so" >> /etc/pam.d/common-session
RUN (cd && echo "ln -s /media/pam_modules/pam_test.so /lib/x86_64-linux-gnu/security/pam_test.so" >> .bashrc)

