import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout


class MyApp(QWidget):

	def __init__(self):
		super().__init__()

		self.initUI()

	def initUI(self):
# QLabel 클래스를 이용해서 라벨 텍스트를 넣어 세 개의 라벨 위젯을 만듭니다.
		lbl_red = QLabel('Red')
		lbl_green = QLabel('Green')
		lbl_blue = QLabel('Blue')
		lbl_etc = QLabel('Yellow')
# setStyleSheet() 메서드를 이용해서 글자색을 빨간색(red)으로, 경계선을 실선(solid)으로, 경계선 두께를 2px로, 경계선 색을 #FA8072로, 경계선의 모서리를 3px만큼 둥글게 설정합니다. 
		lbl_red.setStyleSheet("color: red;"
                              "border-style: solid;"
                              "border-width: 2px;"
                              "border-color: #FA8072;"
                              "border-radius: 3px")
		lbl_green.setStyleSheet("color: green;"
                                "background-color: #7FFFD4")
		lbl_blue.setStyleSheet("color: blue;"
                               "background-color: #87CEFA;"
                               "border-style: dashed;"
                               "border-width: 3px;"
                               "border-color: #1E90FF")
		lbl_etc.setStyleSheet("color: yello;"
                                "background-color: #FFFF00")
# 수직 박스 레이아웃(QVBoxLayout())을 이용해서 세 개의 라벨 위젯을 수직으로 배치합니다.
        vbox = QVBoxLayout()
        vbox.addWidget(lbl_red)
        vbox.addWidget(lbl_green)
        vbox.addWidget(lbl_blue)
	vbox.addWidget(lbl_etc)
        self.setLayout(vbox)

        self.setWindowTitle('Stylesheet')
        self.setGeometry(300, 300, 300, 200)
        self.show()


if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())
