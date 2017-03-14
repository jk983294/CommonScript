#!/usr/bin/env bash

df -h > df.txt
mail -s df jk < df.txt                                  # send email to user jk, the subject is df


mail                                                    # check user's local mail box
# 1                                                     # read 1st email content
# q                                                     # quit local mail box

# MTA(Mail Transfer Agent) SMTP TCP 25
# Postfix, /etc/postfix/main.cf
# Sendmail
# Exim
