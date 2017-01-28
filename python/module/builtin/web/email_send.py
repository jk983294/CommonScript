import smtplib

# send email
server = smtplib.SMTP('localhost')
server.sendmail(from_addr='475154837', to_addr='983294', msg="""To: 983294@qq.com
    From: 475154837@qq.com
    Greetings from Python... :)
    """)
server.quit()
