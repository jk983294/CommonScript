import smtplib

# send email
server = smtplib.SMTP('localhost')
server.sendmail(from_addr='somebody1', to_addr='somebody2', msg="""To: somebody2@gmail.com
    From: somebody1@gmail.com
    Greetings from Python... :)
    """)
server.quit()
