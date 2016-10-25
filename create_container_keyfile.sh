#!/usr/bin/env bash

echo "./create_container_keyfile container keyfile"

cryptsetup --verbose --cipher "aes-cbc-essiv:sha256" --key-size 256 --verify-passphrase luksFormat $1

cryptsetup luksDump $1

dd if=/dev/random of=$2 bs=1 count=32

cryptsetup luksAddKey $1 $2