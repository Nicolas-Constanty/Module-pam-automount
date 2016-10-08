

//#include <...>

//pam_sm_authenticate()
//pam_sm_setcred()
//pam_sm_acct_mgmt()
//pam_sm_open_session()
//pam_sm_close_session()
//pam_sm_chauthtok()
#include <string>
#include "Command.hpp"
extern "C" {
  #include <security/pam_modules.h>
  #include <security/pam_appl.h>
  #include <security/pam_misc.h>
  #include <pwd.h>
  #include <crypt.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>

  PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv)
  {
    printf("%s\n", "pam_sm_chauthtok");
    return PAM_SUCCESS;
  }

  PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv)
  {
    printf("%s\n", "pam_sm_setcred");
    return PAM_SUCCESS;
  }

  PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
  {
    printf("%s\n", "pam_sm_acct_mgmt");
    return PAM_SUCCESS;
  }

  PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
  {
    //printf("%s\n", "pam_sm_open_session");
    const char *c_user;
    int ret;
    ret = pam_get_user(pamh, &c_user, NULL);
    if (ret  == PAM_SUCCESS )
    {
        printf("user");
      if (Command::decrypt_file(c_user) == -1)
          return PAM_CONV_ERR;
          printf("decrypt");
      if (Command::format_partifion(c_user) == -1)
          return PAM_CONV_ERR;
          printf("format");
      if (Command::mount_partition(c_user) == -1)
          return PAM_CONV_ERR;
          printf("mount");
      printf("User file decrypt in : /mnt/decrypt_%s\n", c_user);
    }
    return ret;
  }

  PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
  {
      const char *c_user;
      int ret;

      ret = pam_get_user(pamh, &c_user, NULL);
      if (ret == PAM_SUCCESS)
      {
          if (Command::umount_partition(c_user) == -1)
            return PAM_CONV_ERR;
          if (Command::encrypt_file(c_user) == -1)
            return PAM_CONV_ERR;
          if (Command::remove_volume(c_user) == -1)
            return PAM_CONV_ERR;
          printf("%s\n", "pam_sm_close_session");
      }
      return ret;
  }

  PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flgs, int c, const char **v )
  {
    printf("%s\n", "pam_sm_authenticate");
    char *pass;
    pass = (char *)malloc(256);
    if ( (pam_get_item(pamh, PAM_AUTHTOK, (const void **)&pass)) == PAM_SUCCESS )
    {
      printf("PASS_AUTH=%s\n", pass);
    }
    pam_set_data(pamh,"Pass-word", pass, NULL);
    char *data;
    data = (char *)malloc(256);
    pam_get_data(pamh, "Pass-word", (const void **)&data);
    printf("DATA=%s\n", data);
    return PAM_SUCCESS;
  }

};
