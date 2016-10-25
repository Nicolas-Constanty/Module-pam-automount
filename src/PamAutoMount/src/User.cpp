//
// Created by babiole on 09/10/16.
//

#include "../include/User.hpp"

User::User(const char *name, const char *password)
        : m_name(name), m_password(password)
{}

User::~User()
{
}

const std::string &User::get_name() const {
    return (m_name);
}

const std::string &User::get_password() const {
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
