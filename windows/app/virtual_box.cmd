# shared folder with host windows system
sudo mkdir /mnt/shared
sudo mount -t vboxsf share /mnt/shared
# auto mount, add entry in /etc/fstab
share /mnt/shared vboxsf rw,gid=100,uid=1000,auto 0 0
sudo umount -f /mnt/shared

# share folder
# vm device meun, insert guset additions CD image
sudo mkdir /media/cdrom
sudo mount /dev/cdrom /media/cdrom
apt-get install build-essential linux-headers-`uname -r`
/media/cdrom/./VBoxLinuxAdditions.run

VirtualBox putty connection:
sudo apt-get update
sudo apt-get install ssh
netstat -tlp                    # 查看是否出现了tcp 0 0 *:ssh *:* LISTEN的字样，如果出现了则说明ssh安装成功了
# 在VirtualBox设置中网卡2添加一个HostOnly网卡，网卡1保持NAT不变
# Linux可以通过NAT网卡访问到Internet，主机又可以通过HostOnly网卡访问到虚拟机
ifconfig                        # 获得虚拟机的IP