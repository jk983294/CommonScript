from wxpy import *

if __name__ == '__main__':
    bot = Bot()

    # 向文件传输助手发送消息
    bot.file_helper.send('Hello from wxpy!')
