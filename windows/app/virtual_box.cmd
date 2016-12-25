# shared folder with host windows system
sudo mkdir /mnt/shared
sudo mount -t vboxsf share /mnt/shared
# auto mount, add entry in /etc/fstab
share /mnt/shared vboxsf rw,gid=100,uid=1000,auto 0 0
sudo umount -f /mnt/shared