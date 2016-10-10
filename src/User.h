//
// Created by babiole on 09/10/16.
//

#ifndef PAMELA_USER_H
#define PAMELA_USER_H

#include <iostream>
#include <vector>
#include <cstring>
#include <malloc.h>

class User {
private:
    const char *m_name;
    const char *m_password;
    std::vector<std::string> m_encrypt_files;
    std::vector<std::string> m_volume_files;
    const char *m_mount_directory;
public:
    User(const char *name, const char *password, const char *mount);
    ~User();
public:
    const char *get_name() const;

    const char *get_password() const;

    const std::vector<std::string> &get_volume_files() const;

    const std::vector<std::string> &get_encrypt_files() const;

    const char *get_mount_directory() const;

    void add_encrypt_file(const std::string &filename);

    void add_volume_file(const std::string &filename);
};

std::ostream& operator<<(std::ostream& out, const User& user);

std::ostream& operator<<(std::ostream& out, const User* user);

#endif //PAMELA_USER_H


