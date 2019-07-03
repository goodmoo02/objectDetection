import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout
from PyQt5.QtGui import QIcon, QPixmap


class MyApp(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
# QPushButton 클래스로 푸시 버튼을 하나 만듭니다. 첫 번째 파라미터로는 버튼에 나타날 텍스트, 두 번째는 버튼이 속할 부모 클래스를 지정해줍니다.
# 버튼에 단축키(shortcut)를 지정하고 싶으면 아래와 같이 해당 문자 앞에 ampersand('&')를 넣어주면 됩니다. 이 버튼의 단축키는 'Alt+b'가 됩니다.
# setCheckable()을 True로 설정해주면, 선택되거나 선택되지 않은 상태를 유지할 수 있게 됩니다.
# toggle() 메서드를 호출하면 버튼의 상태가 바뀌게 됩니다. 따라서 이 버튼은 프로그램이 시작될 때 선택되어 있습니다.

        btn1 = QPushButton('&Button1', self)
        btn1.setCheckable(True)
        btn1.toggle()

        btn4 = QPushButton('Button4', self)
        btn4.setCheckable(False)
        btn4.toggle()


        btn2 = QPushButton(self)
        btn2.setText('Button&2')

        btn3 = QPushButton('Button3', self)
        btn3.setEnabled(False)

        vbox = QVBoxLayout()
        vbox.addWidget(btn1)
        vbox.addWidget(btn2)
        vbox.addWidget(btn3)
        vbox.addWidget(btn4)
        self.setLayout(vbox)
        self.setWindowTitle('QPushButton')
        self.setGeometry(300, 300, 300, 200)
        self.show()


if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())
