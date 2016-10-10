#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
public:

    static int format_partifion(std::string user);

    static int mount_partition(std::string user);

    static int umount_partition(std::string user);

    static int encrypt_file(std::string user);

    static int remove_volume(std::string user);

    static int decrypt_file(std::string user, const char *password, const char *device_name);
};


#endif //COMMAND_H
