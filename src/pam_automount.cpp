

//#include <...>

//pam_sm_authenticate()
//pam_sm_setcred()
//pam_sm_acct_mgmt()
//pam_sm_open_session()
//pam_sm_close_session()
//pam_sm_chauthtok()
#include <iostream>
#include <unistd.h>

//TODO changer volume_ par une macro generique
//TODO verifier mdp different de nom User


#include "Command.hpp"
#include "User.hpp"
#define  UNUSED __attribute__((unused))

extern "C" {
    #include <stdlib.h>
    #include <security/pam_modules.h>
    #include <sys/mman.h>

    static void clean_authtok(UNUSED pam_handle_t *pamh, void *data, UNUSED int errcode)
    {
        if (data != NULL)
        {
            unsigned int len = (unsigned int) (strlen((char*)data) + 1);
            memset(data, 0, len);
            munlock(data, len);
            free(data);
        }
    }

    static void clean_user(UNUSED pam_handle_t *pamh, void *data, UNUSED int errcode)
    {
        User *user;

        std::cout << "CLEAN" << std::endl;
        user = (User *)data;
        if (user)
        {
            delete user;
        }
    }

    static int set_authok(pam_handle_t *pamh, const char *user, char **authtok)
    {
        int ret;
        char *ptr = NULL;

        ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&ptr);
        if (ret == PAM_SUCCESS && ptr != NULL)
        {
            *authtok = strdup(ptr);
        }
        else
        {
            struct passwd *pe;
            pe = getpwnam(user);
            if (pe->pw_passwd)
                *authtok = strdup(pe->pw_passwd);
        }
        std::cout << "PASS=" << *authtok << "!" << std::endl;
        if (*authtok != NULL)
        {
            ret = pam_set_data(pamh, "pam_automount_authtok", (void *)(*authtok), clean_authtok);
            if (ret == PAM_SUCCESS)
            {
                if (mlock(authtok, strlen(*authtok) + 1) < 0)
                    std::cout << "Error mlock" << std::endl;
            }
        }
        return (ret);
    }

    PAM_EXTERN int pam_sm_chauthtok(UNUSED pam_handle_t *pamh, UNUSED int flags, UNUSED int argc, UNUSED const char **argv)
  {
      std::cout << "pam_sm_chauthtok" << std::endl;
    return PAM_SUCCESS;
  }

  PAM_EXTERN int pam_sm_setcred(UNUSED pam_handle_t *pamh, UNUSED int flags, UNUSED int argc, UNUSED const char **argv)
  {
      std::cout << "pam_sm_setcred" << std::endl;
    return PAM_SUCCESS;
  }

  PAM_EXTERN int pam_sm_acct_mgmt(UNUSED pam_handle_t *pamh, UNUSED int flags, UNUSED int argc, UNUSED const char **argv)
  {
    std::cout << "pam_sm_acct_mgmt" << std::endl;
    return PAM_SUCCESS;
  }

    PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, UNUSED int flags,
       UNUSED int ac, UNUSED const char **av)
    {
        std::cout << "pam_sm_open_session" << std::endl;
        User *user;
        Command cmd = Command();

        user = NULL;
        if (pam_get_data(pamh, "pam_automount_user", (const void **)&user) != PAM_SUCCESS)
        {
            return (PAM_SESSION_ERR);
        }
        if (user == NULL)
        {
          std::cerr << "User not found" << std::endl;
          return (PAM_SESSION_ERR);
        }
        std::cout << user << std::endl;
        if (std::string(user->get_name()) == "root")
        {
            return (PAM_SUCCESS);
        }
        if (!cmd.init_cryptsetup("/home/" +  std::string(user->get_name()) + "/crypt_" + std::string(user->get_name())))
            return (PAM_SESSION_ERR);

        std::string vol = "volume_" + std::string(user->get_name());
        if (!cmd.luksOpen(vol, user->get_password()))
            return (PAM_SESSION_ERR);
        if (!cmd.mount_volume("/dev/mapper/" + vol, user->get_mount_directory(), "ext4"))
            return (PAM_SESSION_ERR);
        return (PAM_SUCCESS);
    }

    PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, UNUSED int flags,
       UNUSED int ac, UNUSED const char **av)
    {
        User *user;
        Command cmd = Command();

        user = NULL;
        std::cout << "pam_sm_close_session" << std::endl;
        if (pam_get_data(pamh, "pam_automount_user", (const void **)&user) != PAM_SUCCESS)
        {
            return (PAM_SESSION_ERR);
        }
        std::cout << "USER" << std::endl;
        if (user == NULL)
        {
          std::cerr << "user not found" << std::endl;
          return (PAM_SESSION_ERR);
        }
        if (!cmd.umount_volume(user->get_mount_directory()))
        {
            return (PAM_SESSION_ERR);
        }
        if (!cmd.luksClose("volume_" + std::string(user->get_name())))
        {
            return (PAM_SESSION_ERR);
        }
        return (PAM_SUCCESS);
    }

    int save_user(pam_handle_t *pamh)
    {
        int ret;
        const char *c_user;
        User *user;
        char *pass;

        pass = NULL;
        ret = pam_get_user(pamh, &c_user, NULL);
        if (ret != PAM_SUCCESS)
        {
            return PAM_AUTH_ERR;
        }
        set_authok(pamh, c_user, &pass);
        std::string mount_dir = "/mnt/decrypt_" + std::string(c_user);
        user = new User(strdup(c_user), strdup(pass), strdup(mount_dir.c_str()));
        if (pam_set_data(pamh, "pam_automount_user", (void *)user, clean_user) != PAM_SUCCESS)
        {
            return PAM_AUTH_ERR;
        }
        return PAM_SUCCESS;
    }

    PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, UNUSED int flgs,
       UNUSED int ac, UNUSED const char **av )
    {
        std::cout << "pam_sm_authenticate" << std::endl;
        if (save_user(pamh) != PAM_SUCCESS)
            return PAM_AUTH_ERR;
        return PAM_SUCCESS;
    }

};
