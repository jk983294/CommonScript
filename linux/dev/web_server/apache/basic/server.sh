# setup host name
hostnamectl set-hostname zeus
cat /etc/hostname

# man
man openssl
man x509
man rsa
man req


# apache
apt-get install apache
systemctl enable httpd
systemctl start httpd
cat "hello" > /srv/http/index.html
cat "world" > /srv/vhosts/sales/index.html
mkdir /srv/http/downloads

apachectl -M                # list all modules
apachectl configtest        # check config file
systemctl restart httpd

### auth
htpasswd -c sales.pwd kun
htpasswd sales.pwd joe

### no need to restart apache server
.htaccess

### cgi
http://zeus/cgi-bin/report.sh
http://zeus/test.php

# SSL/TLS(transport layer security)
SSLv2 -> SSLv3 -> TLSv1.0 -> TLSv1.1 -> TLSv1.2 -> TLSv1.3
CIA triad: Confidentiality, Integrity, Authenticity

## generate server private key
openssl version  # 1.0.2f before buggy
cd /etc/httpd/conf
openssl genrsa -out server.key 2048
cat server.key
openssl rsa -noout -text -in server.key

## generate server public key
openssl req -new -key server.key -out server.csr

## sign with private key to create certificate
openssl x509 -req -sha256 -in server.csr -signkey server.key -out server.crt

## ssl cipher suite
openssl ciphers -v 'HIGH:MEDIUM:!aRSA'

## register via Let's encrypt
git clone https://github.com/diafygi/acme-tiny
cp acme-tiny/acme_tiny.py /usr/local/bin/
chmod +x /usr/local/bin/acme_tiny.py
mkdir -p /srv/http/.well-known/acme-challenge
openssl genrsa -out le.key 2048
acme_tiny.py --account-key le.key --csr server.csr --acme-dir /srv/http/.well-known/acme-challenge > server.crt

wget http:cert.int-x3.letsencrypt.org/ -O issue.der
openssl x509 -in issue.der -inform DER -out issue.crt -outform PEM
cat issue.crt >> server.crt
