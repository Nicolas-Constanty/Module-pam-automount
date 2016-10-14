//
// Created by babiole on 09/10/16.
//

#include "User.hpp"

User::User(const char *name, const char *password, const char * mount)
        : m_name(name), m_password(password), m_mount_directory(mount)
{}

User::~User()
{
//    if (m_name)
//        free((char *)m_name);
//    if (m_password)
//    {
//        memset((char *)m_password, 0, strlen(m_password));
//        free((char *)m_password);
//    }
//    if (m_mount_directory)
//        free((char *)m_mount_directory);
}

// Getter
const char *User::get_name() const {
    return (m_name);
}

const char *User::get_password() const {
    return (m_password);
}

const std::vector<std::string> &User::get_encrypt_files() const {
    return (m_encrypt_files);
}

const std::vector<std::string> &User::get_volume_files() const {
    return (m_volume_files);
}

const char *User::get_mount_directory() const {
    return (m_mount_directory);
}


// Setter
void User::add_encrypt_file(const std::string &filename)
{
    m_encrypt_files.push_back(filename);
}

void User::add_volume_file(const std::string &filename)
{
    m_volume_files.push_back(filename);
}

std::ostream& operator<<(std::ostream& out, const User& user)
{
    out << "Object User{" << std::endl
        << "\tName : " << user.get_name() << "," << std::endl
        << "\tPassword : " << user.get_password() << "," << std::endl
        << "\tMount directory : " << user.get_mount_directory() << std::endl
        << "}";
    return out;
}

std::ostream& operator<<(std::ostream& out, const User* user)
{
    out << "Object User{" << std::endl
        << "\tName : " << user->get_name() << "," << std::endl
        << "\tPassword : " << user->get_password() << "," << std::endl
        << "\tMount directory : " << user->get_mount_directory() << std::endl
        << "}";
    return out;
}
