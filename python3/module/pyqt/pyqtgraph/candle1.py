from PyQt5 import QtCore, QtGui
import pyqtgraph as pg
import pandas as pd


class UiMainWindow(object):
    def setup_ui(self, main_window):
        main_window.setObjectName("MainWindow")
        main_window.resize(800, 600)
        self.centralwidget = QtGui.QWidget(main_window)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.centralwidget)
        self.verticalLayout_2.setObjectName("verticalLayout")
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        main_window.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(main_window)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 31))
        self.menubar.setObjectName("menubar")
        main_window.setMenuBar(self.menubar)

        self.drawChart = DrawChart()
        self.verticalLayout_2.addWidget(self.drawChart.pyqtgraphDrawChart())

        main_window.setWindowTitle("MainWindow")
        QtCore.QMetaObject.connectSlotsByName(main_window)


class DrawChart(object):
    def __init__(self):
        self.data_list, self.t = self.get_data()

    def pyqtgraphDrawChart(self):
        try:
            self.item = CandlestickItem(self.data_list)
            self.xdict = {
                0: str(self.data_list[0][1]).replace('-', '/'),
                int((self.t + 1) / 2) - 1: str(self.data_list[int((self.t + 1) / 2)][1]).replace('-', '/'),
                self.t - 1: str(self.data_list[-1][1]).replace('-', '/')
            }
            self.string_axis = pg.AxisItem(orientation='bottom')
            self.string_axis.setTicks([self.xdict.items()])
            self.plt = pg.PlotWidget(axisItems={'bottom': self.string_axis}, enableMenu=False)

            self.plt.addItem(self.item)
            return self.plt
        except:
            return pg.PlotWidget()

    def get_data(self):
        df = pd.read_csv('/home/kun/github/math/data/000001.csv')
        df = df.iloc[::-1]
        df['p_change'] = df['close'].pct_change(fill_method='ffill')
        df['ma5'] = df.rolling(window=5)['close'].mean()
        df['ma10'] = df.rolling(window=10)['close'].mean()
        df['ma20'] = df.rolling(window=20)['close'].mean()
        df = df[-300:-1]

        data_list = []
        t = 0
        for idx, row in df.iterrows():
            date, open, high, low, close, volume, amount, p_change, ma5, ma10, ma20 = row[:11]
            datum = (t, date, open, close, low, high, volume, p_change, ma5, ma10, ma20)
            data_list.append(datum)
            t += 1
        return data_list, t


class CandlestickItem(pg.GraphicsObject):
    def __init__(self, data):
        pg.GraphicsObject.__init__(self)
        self.picture = None
        self.data = data
        self.generate_picture()

    def generate_picture(self):
        """
        图片以与平台无关的格式将painter命令序列化到IO设备
        Qt依靠其QColor，QPen和QBrush类来为其所有绘图指定线条和填充样式
        """
        self.picture = QtGui.QPicture()  # 绘制设备, 用于记录和重放QPainter命令
        p = QtGui.QPainter(self.picture)
        p.setPen(pg.mkPen('w'))  # 白色pen
        w = (self.data[1][0] - self.data[0][0]) / 3.  # candle 宽度
        pre_ma5 = 0
        pre_ma10 = 0
        pre_ma20 = 0
        for (t, date, open, close, low, high, volume, p_change, ma5, ma10, ma20) in self.data:
            if open > close:
                p.setPen(pg.mkPen('g'))
                p.setBrush(pg.mkBrush('g'))
            else:
                p.setPen(pg.mkPen('r'))
                p.setBrush(pg.mkBrush('r'))
            p.drawLine(QtCore.QPointF(t, low), QtCore.QPointF(t, high))  # 上下影线
            p.drawRect(QtCore.QRectF(t - w, open, w * 2, close - open))  # candle实体
            if pre_ma5 != 0:
                p.setPen(pg.mkPen('w'))
                p.setBrush(pg.mkBrush('w'))
                p.drawLine(QtCore.QPointF(t-1, pre_ma5), QtCore.QPointF(t, ma5))
            pre_ma5 = ma5
            if pre_ma10 != 0:
                p.setPen(pg.mkPen('c'))
                p.setBrush(pg.mkBrush('c'))
                p.drawLine(QtCore.QPointF(t-1, pre_ma10), QtCore.QPointF(t, ma10))
            pre_ma10 = ma10
            if pre_ma20 != 0:
                p.setPen(pg.mkPen('m'))
                p.setBrush(pg.mkBrush('m'))
                p.drawLine(QtCore.QPointF(t-1, pre_ma20), QtCore.QPointF(t, ma20))
            pre_ma20 = ma20
        p.end()

    def paint(self, p, *args):
        p.drawPicture(0, 0, self.picture)

    def boundingRect(self):
        return QtCore.QRectF(self.picture.boundingRect())


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    MainWindow = QtGui.QMainWindow()
    ui = UiMainWindow()
    ui.setup_ui(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

