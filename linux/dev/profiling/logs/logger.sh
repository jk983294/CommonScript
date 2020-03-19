# making entries in the system log
logger -t Test "This message comes from $USER" 
journalctl -b | grep "This message comes"