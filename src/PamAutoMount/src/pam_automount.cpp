

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

#include <algorithm>
#include "../include/Command.hpp"
#include "../include/User.hpp"
#include "../../ParserCpp/include/IParser.hpp"
#include "../../ParserCpp/include/Parser.hpp"

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

        user = (User *)data;
        if (user)
        {
            delete user;
        }
    }

    static void clean_config(UNUSED pam_handle_t *pamh, void *data, UNUSED int errcode)
    {
        JsonVariant::json_pair *map = (JsonVariant::json_pair *)data;
        if (map)
        {
            delete map;
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

    inline bool file_exist (const std::string& name) {
        struct stat buffer;
        return (stat (name.c_str(), &buffer) == 0);
    }

    PAM_EXTERN int pam_open_volume(Command &cmd, const std::string &path, const std::string &pass, const std::string &name)
    {
        if (file_exist("/home/" + path))
        {
            if (!cmd.init_cryptsetup("/home/" + path))
                return (PAM_SESSION_ERR);
            std::string np = path;
            std::replace(np.begin(), np.end(), '/', '_');
            if (!cmd.luksOpen("volume_" + np, pass))
                return (PAM_SESSION_ERR);
            if (!cmd.mount_volume(name, "/dev/mapper/volume_" + np, "/mnt/decrypt_" + np, "ext4"))
                return (PAM_SESSION_ERR);
        }
        return (PAM_SUCCESS);
    }

    PAM_EXTERN int pam_open_config(User *user,Command &cmd, JsonVariant::json_pair &conf)
    {
        int ret;

        ret = PAM_SESSION_ERR;
        try {
            for (unsigned long j = 0; j < conf["conf"].size(); ++j) {
                if (conf["conf"][j].find(user->get_name()) != conf["conf"][j].end())
                {
                    const JsonVariant &node = conf["conf"][j][user->get_name()];
                    for (unsigned long k = 0; k < node.size(); ++k) {
                        if (node[k].find("filename") != node[k].end())
                        {
                            if (file_exist(node[k]["filename"]()))
                            {
                                std::string path = node[k]["filename"]();
                                path.erase(0, 6);
                                if (node[k].find("keyfile") != node[k].end())
                                {
                                    if (pam_open_volume(cmd, path, node[k]["keyfile"](), user->get_name()))
                                        ret = PAM_SUCCESS;
                                }
                                else
                                {
                                    if (pam_open_volume(cmd, path, user->get_password(), user->get_name()))
                                        ret = PAM_SUCCESS;
                                }
                            }
                        }
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Invalid json" << std::endl;
            return (PAM_SESSION_ERR);
        }
        return ret;
    }

    PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, UNUSED int flags,
                                       UNUSED int ac, UNUSED const char **av)
    {
        std::cout << "pam_sm_open_session" << std::endl;
        int ret;
        User *user;
        JsonVariant::json_pair *pconf;
        Command cmd = Command();

        user = NULL;
        pconf = NULL;
        ret = PAM_SESSION_ERR;
        if (pam_get_data(pamh, "pam_automount_user", (const void **)&user) != PAM_SUCCESS)
            return (PAM_SESSION_ERR);
        if (user == NULL)
        {
            std::cerr << "User not found" << std::endl;
            return (PAM_SESSION_ERR);
        }
        if (user->get_name() == "root")
            return (PAM_SUCCESS);
        if (pam_get_data(pamh, "pam_automount_config", (const void **)&pconf) != PAM_SUCCESS)
        {
            std::cerr << "Config not found" << std::endl;
            return (PAM_SESSION_ERR);
        }
        if (!pconf)
            ret = pam_open_volume(cmd, user->get_name() + "/crypt_" + user->get_name(), user->get_password(), user->get_name());
        else
            ret = pam_open_config(user, cmd, *pconf);
        return (ret);
    }

    PAM_EXTERN int pam_close_volume(Command &cmd, const std::string &path)
    {
        std::string np = path;
        std::replace(np.begin(), np.end(), '/', '_');
        if (!cmd.umount_volume("/mnt/decrypt_" +  np))
        {
            return (PAM_SESSION_ERR);
        }
        if (!cmd.luksClose("volume_" + np))
        {
            return (PAM_SESSION_ERR);
        }
        return (PAM_SUCCESS);
    }

    PAM_EXTERN int pam_close_multiple_volume(User *user, Command &cmd, JsonVariant::json_pair &conf)
    {
        int ret;

        ret = PAM_SESSION_ERR;
        try {
            for (unsigned long j = 0; j < conf["conf"].size(); ++j) {
                if (conf["conf"][j].find(user->get_name()) != conf["conf"][j].end())
                {
                    const JsonVariant &node = conf["conf"][j][user->get_name()];
                    for (unsigned long k = 0; k < node.size(); ++k) {
                        if (node[k].find("filename") != node[k].end())
                        {
                            std::string path = node[k]["filename"]();
                            path.erase(0, 6);
                            if (pam_close_volume(cmd, path))
                                ret = PAM_SUCCESS;
                        }
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Invalid json" << std::endl;
            return (PAM_SESSION_ERR);
        }
        return ret;
    }

    PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, UNUSED int flags,
                                        UNUSED int ac, UNUSED const char **av)
    {
        int ret;
        User *user;
        Command cmd = Command();
        JsonVariant::json_pair *pconf;

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
        if (user->get_name() == "root")
            return (PAM_SUCCESS);
        if (pam_get_data(pamh, "pam_automount_config", (const void **)&pconf) != PAM_SUCCESS)
        {
            std::cerr << "Config not found" << std::endl;
            return (PAM_SESSION_ERR);
        }
        if (!pconf)
            ret = pam_close_volume(cmd, user->get_name() + "_crypt_" + user->get_name());
        else
            ret = pam_close_multiple_volume(user, cmd, *pconf);
        return (ret);
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
        user = new User(strdup(c_user), strdup(pass));
        if (pam_set_data(pamh, "pam_automount_user", (void *)user, clean_user) != PAM_SUCCESS)
        {
            return PAM_AUTH_ERR;
        }
        return PAM_SUCCESS;
    }

    int save_config(pam_handle_t *pamh, void *config)
    {
        if (pam_set_data(pamh, "pam_automount_config", config, clean_config) != PAM_SUCCESS)
            return PAM_AUTH_ERR;
        return PAM_SUCCESS;
    }

    PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, UNUSED int flgs,
                                       UNUSED int ac, UNUSED const char **av )
    {
        std::cout << "pam_sm_authenticate" << std::endl;
        if (save_user(pamh) != PAM_SUCCESS)
            return PAM_AUTH_ERR;
        try {
            Parser parser = Parser(JSON, (char *) "/etc/pam.d/users.json");
            JsonVariant::json_pair *map = new JsonVariant::json_pair();
            if (parser.parse(map))
                save_config(pamh, map);
            else
                save_config(pamh, NULL);
        }
        catch (const std::exception &e)
        {
            save_config(pamh, NULL);
        }
        return PAM_SUCCESS;
    }
};
