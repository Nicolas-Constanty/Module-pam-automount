//
// Created by babiole on 09/10/16.
//

#include "../include/User.hpp"

User::User(const char *name, const char *password)
        : m_name(name), m_password(password)
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

std::ostream& operator<<(std::ostream& out, const User& user)
{
    out << "Object User{" << std::endl
        << "\tName : " << user.get_name() << "," << std::endl
        << "\tPassword : " << user.get_password() << std::endl
        << "}";
    return out;
}

std::ostream& operator<<(std::ostream& out, const User* user)
{
    out << "Object User{" << std::endl
        << "\tName : " << user->get_name() << "," << std::endl
        << "\tPassword : " << user->get_password() << std::endl
        << "}";
    return out;
}
