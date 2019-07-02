import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QAction, qApp
from PyQt5.QtGui import QIcon
class MyApp(QMainWindow):
	def __init__(self):
		super().__init__()
		self.initUI()
	def initUI(self):
		exitAction = QAction(QIcon('exit.png'), 'Exit', self)
		exitAction.setShortcut('Ctrl+Q')
		exitAction.setStatusTip('Exit application')
		exitAction.triggered.connect(qApp.quit)
		insertFileAction = QAction(QIcon('file.png'), 'Insert_file', self)
		insertFileAction.setShortcut('Ctrl+F')
		insertFileAction.setStatusTip('Insert file')
		#insertFileAction.triggered.connect()
		self.statusBar()
		menubar = self.menuBar()
		menubar.setNativeMenuBar(False)
		fileMenu = menubar.addMenu('&File')
		fileMenu2 = menubar.addMenu('&Insert')
		fileMenu.addAction(exitAction)
		fileMenu2.addAction(insertFileAction)
		self.setWindowTitle('Menubar')
		self.setGeometry(300, 300, 300, 200)
		self.show()
if __name__ == '__main__':
	app = QApplication(sys.argv)
	ex = MyApp()
	sys.exit(app.exec_())
