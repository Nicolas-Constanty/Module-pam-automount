//
// Created by babiole on 09/10/16.
//

#include <unistd.h>
#include <stdlib.h>
#include "../include/Command.hpp"


Command::Command() {
    _loopname = NULL;
    _cd = NULL;
}

bool Command::init_cryptsetup()
{
    if (_loopname)
    {
        if (crypt_init(&_cd, _loopname) == -1 ) {
            display_err("crypt_init() failed for " + std::string(_loopname));
            return (false);
        }
    }
    else
    {
        display_err("Call init_cryptsetup(filename) or Call init_loop_device before");
        return (false);
    }
    return (true);
}

bool Command::init_cryptsetup(const std::string &filename)
{
    if (crypt_init(&_cd, filename.c_str()) == -1 ) {
        display_err("crypt_init() failed for " + filename);
        return (false);
    }
    return (true);
}

bool Command::load()
{
    if (crypt_load(_cd, CRYPT_LUKS1, NULL) == -1) {
        display_err("crypt_load() failed on device " + std::string(crypt_get_device_name(_cd)) + std::to_string(errno));
        return (false);
    }
    return (true);
}

bool Command::activate_by_passphrase(const std::string &device_name, const char *password)
{
    int r;
    r = crypt_activate_by_passphrase(_cd,
                                     device_name.c_str(),
                                     CRYPT_ANY_SLOT,
                                     password, strlen(password),
                                     CRYPT_ACTIVATE_ALLOW_DISCARDS);
    if (r < 0 && r != -EEXIST) {
        display_err("Device " + device_name + " activation failed err " + strerror(r));
        crypt_free(_cd);
        _cd = NULL;
        return (false);
    }
    crypt_free(_cd);
    _cd = NULL;
    return (true);
}

Command::~Command()
{
    if (_cd)
        crypt_free(_cd);
    if (_loopname)
        free(_loopname);
}

bool Command::luksOpen(const std::string &device_name, const char *password)
{
    if (_cd == NULL)
    {
        display_err("Call init_cryptsetup(filename) must be call before");
        return (false);
    }
    return (load() && activate_by_passphrase(device_name, password));
}

bool Command::create_free_loop_device()
{
    int ctrl_loop;
    long dev_nbr;

    // Find a free loop device
    ctrl_loop = open("/dev/loop-control", O_RDWR);
    if (ctrl_loop == -1)
    {
        display_err("Failed open: /dev/loop-control");
        return (false);
    }

    // Setup information
    dev_nbr = ioctl(ctrl_loop, LOOP_CTL_GET_FREE);
    if (dev_nbr == -1)
    {
        display_err("Failed to set loop device information : ioctl-LOOP_CTL_GET_FREE");
        close(ctrl_loop);
        return (false);
    }
    _loopname = strdup(std::string("/dev/loop" + std::to_string(dev_nbr)).c_str());
    std::cout << "loopname = " << _loopname << std::endl;
    return (true);
}

bool  Command::associate_loop_device(const std::string &filename)
{
    int container_fd;
    int loopfd;

    // Open container
    std::cout << "Container : " << filename << std::endl;
    container_fd = open(filename.c_str(), O_RDWR);
    if (container_fd == -1)
    {
        display_err("init_loop_device : Failed to open " + filename);
        return (false);
    }
    // Open free loop device
    loopfd = open(_loopname, O_RDWR);
    if (loopfd == -1)
    {
        display_err("init_loop_device : Failed to open " + std::string(_loopname));
        close(container_fd);
        return (false);
    }
    // Attach loop device with container
    if (ioctl(loopfd, LOOP_SET_FD, container_fd) == -1)
    {
        display_err("Failed to set loop device information : ioctl-LOOP_SET_FD");
        close(container_fd);
        close(loopfd);
        return (false);
    }
    close(container_fd);
    close(loopfd);
    return (true);
}

bool Command::init_loop_device(const std::string &filename)
{
    return (create_free_loop_device() && associate_loop_device(filename));
}

void Command::display_err(const std::string &msg)
{
    std::cerr << msg << std::endl;
}

bool Command::detach_loop_device()
{
    int		loopfd;

    if (!_loopname)
        return (true);
    if ((loopfd = open(_loopname, O_RDWR)) < 0)
    {
        display_err("Failed to open loop device : " + std::string(strerror(errno)) + ".");
        return (false);
    }
    if (ioctl(loopfd, LOOP_CLR_FD) < 0) {
        close(loopfd);
        display_err("Failed to detach loop device : " + std::string(strerror(errno)) + ".");
        return (false);
    }
    return (true);
}

bool Command::mount_volume(const std::string &source, const std::string &target, const std::string &filesystemtype)
{
    if (mkdir(target.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) < 0 && errno != EEXIST)
    {
        display_err("mkdir : " + std::string(strerror(errno)));
        return (false);
    }
    std::string fsys_cmd = "mkfs.ext4 -j " + source;
    if (system(fsys_cmd.c_str()) == -1)
    {
        display_err("mkfs failled");
        return (false);
    }
    if (mount(source.c_str(), target.c_str(), filesystemtype.c_str(), 0, NULL) < 0)
    {
        display_err("mount : " + std::string(strerror(errno)));
        return (false);
    }
    return (true);
}

bool Command::umount_volume(const std::string &volume)
{
    if (!detach_loop_device())
    {
        return (false);
    }
    if (umount(volume.c_str()) < 0)
    {
        display_err("umount : " + std::string(strerror(errno)));
        return (false);
    }
    if (rmdir(volume.c_str()) < 0)
    {
        display_err("rmdir : " + std::string(strerror(errno)));
        return (false);
    }
    return (true);
}

bool Command::luksClose(const std::string &device_name)
{
    if (crypt_init_by_name(&_cd, device_name.c_str()) < 0)
    {
        display_err("crypt_init_by_name() failed for " + device_name + ".");
        return (false);
    }

    if (crypt_status(_cd, device_name.c_str()) != CRYPT_ACTIVE)
    {
        display_err("Something failed perhaps, device " + device_name + " is not active.");
        crypt_free(_cd);
        _cd = NULL;
        return (false);
    }
    if (crypt_deactivate(_cd, device_name.c_str()) < 0)
    {
        display_err("crypt_deactivate() failed.");
        crypt_free(_cd);
        _cd = NULL;
        return (false);
    }
    std::cout << "Device " << device_name << " is now deactivated." << std::endl;
    crypt_free(_cd);
    _cd = NULL;
    return (true);
}
