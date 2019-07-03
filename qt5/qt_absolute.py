# 절대적 배치(absolute positioning) 방식은 각 위젯의 위치와 크기를 픽셀 단위로 설정해서 배치합니다. 절대 배치 방식을 사용할 때는 다음의 제약을 이해하고 있어야 합니다.

       # 창의 크기를 조절해도 위젯의 크기와 위치는 변하지 않는다.
       # 다양한 플랫폼에서 어플리케이션이 다르게 보일 수 있다.
       # 어플리케이션의 폰트를 바꾸면 레이아웃이 망가질 수 있다.
       # 레이아웃을 바꾸고 싶다면 완전히 새로 고쳐야 하며, 이는 매우 번거롭다.


#    두 개의 라벨과 두 개의 푸시버튼 위젯을 절대적 배치 방식으로 배치해 보겠습니다.

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QPushButton


class MyApp(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        label1 = QLabel('Label1', self)
# 라벨을 하나 만들고, x=20, y=20에 위치하도록 옮겨줍니다. 
        label1.move(20, 20)
        label2 = QLabel('Label2', self)
        label2.move(20, 60)

        btn1 = QPushButton('Button1', self)
        btn1.move(80, 13)
        btn2 = QPushButton('Button2', self)
        btn2.move(80, 53)

        self.setWindowTitle('Absolute Positioning')
        self.setGeometry(300, 300, 400, 200)
        self.show()


if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())

