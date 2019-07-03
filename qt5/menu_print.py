import math
import sys

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QApplication, QGridLayout, QCheckBox, QPushButton, QVBoxLayout, QHBoxLayout, QLayout, QLineEdit,
        QSizePolicy, QToolButton, QWidget)

class Menu_print(QWidget):
    def __init__(self):
        super().__init__()

        self.waitingForOperand = True

        # create window & button
        self.display = QLineEdit('Click menu')
        self.display.setReadOnly(True)
        self.display.setAlignment(Qt.AlignRight)
        self.display.setMaxLength(15)

        font = self.display.font()
        font.setPointSize(font.pointSize() + 8)
        self.display.setFont(font)

        cb1 = QCheckBox('jja_jang', self)
        cb1.toggle()
        cb1.stateChanged.connect(self.Checked)

        cb2 = QCheckBox('jjam_bbong', self)
        cb2.toggle()
        cb2.stateChanged.connect(self.Checked)

        cb3 = QCheckBox('tang_su_yuk', self)
        cb3.toggle()
        cb3.stateChanged.connect(self.Checked)
        
        clearButton = QPushButton('reset', self)
        clearButton.released.connect(self.Checked)

        # draw window & button
        self.setWindowTitle('menu_print')
        self.setGeometry(300, 300, 300, 200)

        mainLayout = QVBoxLayout()
        mainLayout.addWidget(self.display)
        mainLayout.addWidget(cb1)
        mainLayout.addWidget(cb2)
        mainLayout.addWidget(cb3)

        hbox = QHBoxLayout()
        hbox.addStretch(1)
        hbox.addWidget(clearButton)
        hbox.addStretch(1)

        mainLayout.addStretch(1)
        mainLayout.addLayout(hbox)
        mainLayout.addStretch(1)

        self.setLayout(mainLayout)

        # for i in range(Calculator.NumDigitButtons):
        #     self.digitButtons.append(self.createButton(str(i),
        #             self.Checked))

    def Checked(self):
        checkedButton = self.sender()
        print(checkedButton.text())
        Value = 'menu'
        # Value = checkedButton.text()
        if Value == 'reset':
            self.display.clear()
            self.display.setText('Click menu')
            return

        if self.display.text() == 'Click menu':
            self.display.clear()
            self.display.setText(self.display.text() + Value)

        else:
            self.display.text().replace(Value, "", 1)

    

if __name__ == '__main__':

    app = QApplication(sys.argv)
    menu = Menu_print()
    menu.show()

    sys.exit(app.exec_())

