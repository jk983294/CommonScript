from wxpy import *

if __name__ == '__main__':
    bot = Bot()

    # 在 Web 微信中把自己加为好友
    bot.self.add()
    bot.self.accept()

    # 发送消息给自己
    bot.self.send('能收到吗？')
    bot.join()
    bot.logout()
