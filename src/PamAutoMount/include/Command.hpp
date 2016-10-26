//
// Created by babiole on 09/10/16.
//

#ifndef PAMELA_COMMAND_H
#define PAMELA_COMMAND_H

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <linux/loop.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <libcryptsetup.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include "../../ParserCpp/include/JsonVariant.hpp"

class Command {
private:
    struct crypt_device *_cd;
    struct crypt_active_device _cad;
    char *_loopname;

public:
    Command();
    ~Command();

    // Public loop device function
public:
    bool init_loop_device(const std::string &filename);

    // Public CrypSetup functions
public:
    bool init_cryptsetup();
    bool init_cryptsetup(const std::string &filename);
    bool luksOpen(const std::string &device_name, const std::string &password);
    bool luksClose(const std::string &filename);
    bool create_file(std::map<std::string, JsonVariant> &);

    // Public Mount functions
public:
    bool mount_volume(const std::string &name, const std::string &source, const std::string &target, const std::string &filesystemtype);
    bool umount_volume(const std::string &volume);

    // Loop device functions
private:
    bool create_free_loop_device();
    bool associate_loop_device(const std::string &filename);
    bool detach_loop_device();

    // CryptSetup functions
private:
    bool load();
    bool activate_by_passphrase(const std::string &device_name, const std::string &password);
    bool activate_by_keyfile(const std::string &device_name, const std::string &password);

    // Util functions
private:
    void display_err(const std::string &msg);

    // Create file function
private:
    bool create_file(const std::string &filename);
    bool create_file(const std::string &filename, const std::string &size);
    bool create_file(const std::string &filename, const std::string &size, const std::string &mode);
    bool create_file_keyfile(const std::string &filename, const std::string &keyfile);
    bool create_file_keyfile(const std::string &filename, const std::string &keyfile, const std::string &size);
    bool create_file_keyfile(const std::string &filename, const std::string &keyfile, const std::string &size, const std::string &mode);
};


#endif //PAMELA_COMMAND_H
