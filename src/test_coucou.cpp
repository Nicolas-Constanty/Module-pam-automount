

//#include <...>

//pam_sm_authenticate()
//pam_sm_setcred()
//pam_sm_acct_mgmt()
//pam_sm_open_session()
//pam_sm_close_session()
//pam_sm_chauthtok()
#include <string>
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
    std::string user;
    const char *c_user;
    std::string crypt_file;
    std::string crypt_cmd;
    std::string fsys_cmd;
    std::string vol;
    std::string mount_cmd;
    char *pass;
    pass = (char *)malloc(256);

    if ( (pam_get_user(pamh, &c_user, NULL )) == PAM_SUCCESS )
    {
      printf("USER=%s!\n", c_user);
    }
    user = c_user;
    crypt_file = "/home/" + user + "/crypt_" + user;
    crypt_cmd = "cryptsetup luksOpen " + crypt_file + " volume_" + user;
    system(crypt_cmd.c_str());
    fsys_cmd = "mkfs.ext4 -j /dev/mapper/volume_" + user;
    system(fsys_cmd.c_str());
    mount_cmd = "mkdir /mnt/decrypt_" + user + " && mount /dev/mapper/volume_" + user + " /mnt/decrypt_" + user;
    system(mount_cmd.c_str());
    printf("User file decrypt in : /mnt/decrypt_%s\n", user.c_str());
    return PAM_SUCCESS;
  }

  PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
  {
    const char *c_user;
    std::string umount_cmd;
    std::string close_cmd;
    std::string clear_cmd;
    std::string user;

    if ( (pam_get_user(pamh, &c_user, NULL )) == PAM_SUCCESS )
    {
      printf("%s\n", c_user);
    }
    user = c_user;
    umount_cmd = "umount /mnt/decrypt_" + user;
    close_cmd = "cryptsetup luksClose volume_" + user;
    clear_cmd = "rm -rf /mnt/decrypt_" + user;
    system(umount_cmd.c_str());
    system(close_cmd.c_str());
    system(clear_cmd.c_str());
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

};
