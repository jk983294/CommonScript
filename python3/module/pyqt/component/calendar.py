import sys
from PyQt5.QtWidgets import (QWidget, QCalendarWidget, QLabel, QApplication)
from PyQt5.QtCore import QDate


class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.lbl = None
        self.init_ui()

    def init_ui(self):
        cal = QCalendarWidget(self)
        cal.setGridVisible(True)
        cal.move(20, 20)
        # 从部件选择一个日期,点击[QDate]发出信号。我们将这个信号连接到用户定义的show_date()方法
        cal.clicked[QDate].connect(self.show_date)

        self.lbl = QLabel(self)
        date = cal.selectedDate()
        self.lbl.setText(date.toString())
        self.lbl.move(130, 260)

        self.setGeometry(300, 300, 350, 300)
        self.setWindowTitle('Calendar')
        self.show()

    def show_date(self, date):
        self.lbl.setText(date.toString())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
