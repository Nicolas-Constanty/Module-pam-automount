#include <security/pam_modules.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <pwd.h>
#include <crypt.h>
#include <stdlib.h>
//#include <...>

//pam_sm_authenticate()
//pam_sm_setcred()
//pam_sm_acct_mgmt()
//pam_sm_open_session()
//pam_sm_close_session()
//pam_sm_chauthtok()

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
const char *user;

  if ( (pam_get_user(pamh, &user, NULL )) == PAM_SUCCESS )
  {
    printf("%s\n", user);
  }
  printf("%s\n", "pam_sm_open_session");
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  printf("%s\n", "pam_sm_close_session");
  //sleep(5);
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flgs, int c, const char **v )
{
  printf("%s\n", "pam_sm_authenticate");
  return PAM_SUCCESS;
  //const char *user;
  //struct passwd *pwd;
  //char *passwd;
  //int ret;

  /* ignore flags and optional arguments */
  //if ( (ret = pam_get_user(pamh, &user, NULL )) != PAM_SUCCESS )
  //return ret;
  //  if ( (ret = pam_get_pass(pamh, &passwd, NULL )) != PAM_SUCCESS )
  //  return ret;
  //  if ( (pwd = getpwnam(user)) != NULL )
  //  {
  //    if ( !strcmp(pwd->pw_passwd, crypt(passwd)) )
  //  {
  //  return PAM_SUCCESS;
  //}
  //else
  //{
  //  return PAM_AUTH_ERR;
  //}
  //}
  //return PAM_AUTH_ERR;
}

//int main()
//{
  //return (0);
//}
