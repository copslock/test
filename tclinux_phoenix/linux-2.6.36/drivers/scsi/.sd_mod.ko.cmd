cmd_drivers/scsi/sd_mod.ko := mips-buildroot-linux-gnu-ld -r  -m elf32btsmip -T /opt/tclinux_phoenix/linux-2.6.36/scripts/module-common.lds --build-id  -o drivers/scsi/sd_mod.ko drivers/scsi/sd_mod.o drivers/scsi/sd_mod.mod.o