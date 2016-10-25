#!/usr/bin/env bash

echo "./create_container_password container cantainer_size(Mo)"

dd if=/dev/zero of=$1 bs=1M count=$2

cryptsetup -y luksFormat $1