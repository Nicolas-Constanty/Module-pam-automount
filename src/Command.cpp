#include "Command.hpp"

int Command::decrypt_file(std::string user)
{
    std::string crypt_file;
    std::string crypt_cmd;

    crypt_file = "/home/" + user + "/crypt_" + user;
    crypt_cmd = "cryptsetup luksOpen " + crypt_file + " volume_" + user;
    return (system(crypt_cmd.c_str()));
}

int Command::format_partifion(std::string user)
{
    std::string fsys_cmd;

    fsys_cmd = "mkfs.ext4 -j /dev/mapper/volume_" + user;
    return (system(fsys_cmd.c_str()));
}

int Command::mount_partition(std::string user)
{
    std::string mount_cmd;

    mount_cmd = "mkdir /mnt/decrypt_" + user + " && mount /dev/mapper/volume_" + user + " /mnt/decrypt_" + user;
    return (system(mount_cmd.c_str()));
}

int Command::umount_partition(std::string user)
{
    std::string umount_cmd;
    umount_cmd = "umount /mnt/decrypt_" + user;
    return (system(umount_cmd.c_str()));
}

int Command::encrypt_file(std::string user)
{
    std::string close_cmd;
    close_cmd = "cryptsetup luksClose volume_" + user;
    return (system(close_cmd.c_str()));
}

int Command::remove_volume(std::string user)
{
    std::string remove_vol;
    remove_vol = "rm -rf /mnt/decrypt_" + user;
    return (system(remove_vol.c_str()));
}
