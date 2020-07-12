import sys
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *


class DockDemo(QMainWindow):
    def __init__(self):
        super().__init__()

        trade_widget = TradeWidget()
        self.trade_docker = QDockWidget('交易窗口', self)
        self.trade_docker.setWidget(trade_widget)
        self.trade_docker.setFeatures(self.trade_docker.DockWidgetFloatable | self.trade_docker.DockWidgetMovable)
        self.trade_docker.setObjectName("交易窗口")
        self.trade_docker.setFloating(False)

        self.addDockWidget(Qt.RightDockWidgetArea,self.trade_docker)
        tick_widget = TickMonitorWidget()
        self.tick_docker = QDockWidget('行情窗口', self)
        self.tick_docker.setWidget(tick_widget)
        self.tick_docker.setFloating(False)
        self.addDockWidget(Qt.LeftDockWidgetArea, self.tick_docker)
        self.show()


class TradeWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("这里是交易窗口")
        button = QPushButton('交易按钮', self)
        button.move(10, 20)
        self.show()


class TickMonitorWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("这里是行情窗口")
        button = QPushButton('行情', self)
        button.move(10, 20)
        self.show()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    dd = DockDemo()
    sys.exit(app.exec_())
