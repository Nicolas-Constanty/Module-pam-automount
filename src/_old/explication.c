//
// To build:
//
//      gcc pam_password.c -lpam -lpam_misc
//
// To get PAM development library:
//
//      sudo apt-get install libpam-dev          ou libpam0g-dev
//
//

#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>
