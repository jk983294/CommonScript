# shared folder with host windows system
sudo mkdir /mnt/shared
sudo mount -t vboxsf share /mnt/shared
# auto mount, add entry in /etc/fstab
share /mnt/shared vboxsf rw,gid=100,uid=1000,auto 0 0
sudo umount -f /mnt/shared

VirtualBox putty connection:
sudo apt-get update
sudo apt-get install ssh
netstat -tlp                    # �鿴�Ƿ������tcp 0 0 *:ssh *:* LISTEN�������������������˵��ssh��װ�ɹ���
# ��VirtualBox����������2���һ��HostOnly����������1����NAT����
# Linux����ͨ��NAT�������ʵ�Internet�������ֿ���ͨ��HostOnly�������ʵ������
ifconfig                        # ����������IP