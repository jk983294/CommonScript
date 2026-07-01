tar -czvf proj.tar.gz -C ~/cpp proj

tar -czf - -C ~/github piqp | openssl enc -aes-256-cbc -salt -out piqp.tar.gz.enc
openssl enc -d -aes-256-cbc -in piqp.tar.gz.enc | tar -xzf -