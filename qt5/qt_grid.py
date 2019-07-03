# 가장 일반적인 레이아웃 클래스는 '그리드 레이아웃(grid layout)'입니다.
# 이 레이아웃 클래스는 위젯의 공간을 행(row)과 열(column)로 구분합니다.
# 그리드 레이아웃을 생성하기 위해 QGridLayout 클래스를 사용합니다.

import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QGridLayout, QLabel, QLineEdit, QTextEdit)


class MyApp(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        grid = QGridLayout()
        self.setLayout(grid)

        grid.addWidget(QLabel('Title:'), 0, 0)
        grid.addWidget(QLabel('Author:'), 1, 0)
        grid.addWidget(QLabel('Review:'), 2, 0)

        grid.addWidget(QLineEdit(), 0, 1)
        grid.addWidget(QLineEdit(), 1, 1)
# QTextEdit() 위젯은 QLineEdit() 위젯과 달리 여러 줄의 텍스트를 수정할 수 있는 위젯입니다.
# 세 번째 행, 두 번째 열에 배치합니다. 
        grid.addWidget(QTextEdit(), 2, 1)

        self.setWindowTitle('QGridLayout')
        self.setGeometry(300, 300, 300, 200)
        self.show()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())

