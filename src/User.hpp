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
public:
    User(const char *name, const char *passwords);
    ~User();
public:
    const char *get_name() const;

    const char *get_password() const;
};

std::ostream& operator<<(std::ostream& out, const User& user);

std::ostream& operator<<(std::ostream& out, const User* user);

#endif //PAMELA_USER_H
