#!/bin/sh

# Copy files
cp ../bin/amd64/hadron ../bin/amd64/iso/boot/hadron

# Make iso
grub-mkrescue -o ../bin/amd64/hadron.iso ../bin/amd64/iso