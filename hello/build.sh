#!/bin/sh
set -eux
cd "$(dirname "$0")"
echo "Entering directory '$PWD'"
nasm -f elf32 os.nasm
ld -m elf_i386 -n -o os -T os.ld os.o
rm -rf os.iso.files
mkdir os.iso.files
mkdir os.iso.files/boot
mkdir os.iso.files/boot/grub
cp -p grub.cfg os.iso.files/boot/grub/
cp -p os os.iso.files/
grub-mkrescue -o os.iso os.iso.files >os.iso.log 2>&1
