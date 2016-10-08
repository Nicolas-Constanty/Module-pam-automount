

//#include <...>

//pam_sm_authenticate()
//pam_sm_setcred()
//pam_sm_acct_mgmt()
//pam_sm_open_session()
//pam_sm_close_session()
//pam_sm_chauthtok()
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
   const char *user;
   char crypt_cmd[256] = {0};
   char fsys_cmd[256] = {0};
   char crypt_file[256] = {0};
   char vol[256] = {0};
   char mount_cmd[256] = {0};

   if ( (pam_get_user(pamh, &user, NULL )) == PAM_SUCCESS )
   {
     printf("%s\n", user);
   }
   snprintf(crypt_file, 256, "/home/%s/crypt_%s", user, user);
   snprintf(vol, 256, "volume_%s", user);
   char *arguments[] = {"luksOpen", crypt_file, vol, NULL};
   snprintf(crypt_cmd, 256, "echo -n %s | cryptsetup %s %s %s -\n",
   user, arguments[0], arguments[1], arguments[2]);
   system(crypt_cmd);
   snprintf(fsys_cmd, 256, "mkfs.ext4 -j /dev/mapper/volume_%s", user);
   system(fsys_cmd);
   snprintf(mount_cmd, 256, "mkdir /mnt/decrypt_%s && mount /dev/mapper/volume_%s /mnt/decrypt_%s", user, user, user);
   system(mount_cmd);
   printf("User file decrypt in : /mnt/decrypt_%s\n", user);
   return PAM_SUCCESS;
  }

  PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
  {
   const char *user;
   char umount_cmd[256] = {0};
   char close_cmd[256] = {0};
   char clear_cmd[256] = {0};

   if ( (pam_get_user(pamh, &user, NULL )) == PAM_SUCCESS )
   {
     printf("%s\n", user);
   }
   snprintf(umount_cmd, 256, "umount /mnt/decrypt_%s", user);
   snprintf(close_cmd, 256, "cryptsetup luksClose volume_%s", user);
   snprintf(clear_cmd, 256, "rm -rf /mnt/decrypt_%s", user);
   system(umount_cmd);
   system(close_cmd);
   system(clear_cmd);
   printf("%s\n", "pam_sm_close_session");
   return PAM_SUCCESS;
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
