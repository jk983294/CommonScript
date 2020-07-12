import sys
from PyQt5.QtWidgets import *


class Table(QWidget):
    def __init__(self):
        super(Table, self).__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("QTableWidget例子")
        self.resize(400, 300)
        layout = QHBoxLayout()

        # 四行三列
        table_widget = QTableWidget(4, 3)

        # 设置水平方向的表头标签与垂直方向上的表头标签，注意必须在初始化行列之后进行，否则，没有效果
        table_widget.setHorizontalHeaderLabels(['姓名', '性别', '体重（kg）'])

        # 设置垂直方向的表头标签
        table_widget.setVerticalHeaderLabels(['行1', '行2', '行3', '行4'])

        # 设置水平方向表格为自适应的伸缩模式
        # table_widget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

        # 将表格变为禁止编辑
        # table_widget.setEditTriggers(QAbstractItemView.NoEditTriggers)

        # 设置表格整行选中
        # table_widget.setSelectionBehavior(QAbstractItemView.SelectRows)

        # 将行与列的高度设置为所显示的内容的宽度高度匹配
        # QTableWidget.resizeColumnsToContents(table_widget)
        # QTableWidget.resizeRowsToContents(table_widget)

        # 表格头的显示与隐藏
        # table_widget.verticalHeader().setVisible(False)
        # table_widget.horizontalHeader().setVisible(False)

        # 在单元格内放置控件
        # comBox=QComboBox()
        # comBox.addItems(['男','女'])
        # comBox.addItem('未知')
        # comBox.setStyleSheet('QComboBox{margin:3px}')
        # table_widget.setCellWidget(0, 1, comBox)
        #
        # searchBtn=QPushButton('修改')
        # searchBtn.setDown(True)
        # searchBtn.setStyleSheet('QPushButton{margin:3px}')
        # table_widget.setCellWidget(0, 2, searchBtn)

        # 添加数据
        new_item = QTableWidgetItem('张三')
        table_widget.setItem(0, 0, new_item)

        new_item = QTableWidgetItem('男')
        table_widget.setItem(0, 1, new_item)

        new_item = QTableWidgetItem('160')
        table_widget.setItem(0, 2, new_item)

        layout.addWidget(table_widget)

        self.setLayout(layout)


if __name__ == '__main__':
    app=QApplication(sys.argv)
    win=Table()
    win.show()
    sys.exit(app.exec_())
