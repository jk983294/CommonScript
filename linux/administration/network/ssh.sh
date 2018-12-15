#!/bin/bash

netstat -antl                               # check TCP 22 for ssh
ss -alt                                     # check TCP 22 for ssh
lsof -i | grep ssh                          # check TCP 22 for ssh
grep ssh /etc/services

less /etc/ssh/ssh_config
less /etc/ssh/sshd_config

systemctl restart sshd                      # restart after re-configuration

# client authentication
# client public keys in ~/.ssh/authorized_keys
ssh jk@192.168.0.97                         # ssh to remote host with account jk

# key generation, id_rsa, id_rsa.pub
ssh-keygen -t rsa
ssh-keygen -t rsa -C "jk983294@gmail.com" -b 4096
ssh-copy-id -i id_rsa.pub jk@192.168.0.97   # copy public key to remote host's authorized_keys file

# login/copy without password
ssh-keygen -t rsa -b 2048
ssh-copy-id id@server
# then check target machine's ~/.ssh/authorized_keys

# putty client
# putty key generator, generate key pair
# copy the public key to ~/.ssh/authorized_keys
# Connection -> SSH -> Auth -> browse private key file

# ssh tunnel
ssh -f -N -L 8000:localhost:80 user@address.com
# 127.0.0.1:8000 will fetch http://address.com website via ssh encrypt tunnel
