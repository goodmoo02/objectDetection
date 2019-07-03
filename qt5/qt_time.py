# 현재 날짜 출력
from PyQt5.QtCore import QDate, Qt, QTime, QDateTime

# currentDate() 메서드는 현재 날짜를 반환합니다.
now = QDate.currentDate()
# toString() 메서드를 통해 현재 날짜를 문자열로 출력할 수 있습니다.
print(now.toString())

# 날짜 형식 설정

now = QDate.currentDate()

# toString() 메서드의 format 파라미터를 설정함으로써 날짜의 형식을 정할 수 있습니다.
print(now.toString('d.M.yy'))
print(now.toString('dd.MM.yyyy'))
print(now.toString('ddd.MMMM.yyyy'))

# Qt.ISODate, Qt.DefaultLocaleLongDate를 입력함으로써 ISO 표준 형식 또는 어플리케이션의 기본 설정에 맞게 출력할 수 있습니다.
print(now.toString(Qt.ISODate))
print(now.toString(Qt.DefaultLocaleLongDate))


# 현재 시간 출력하기
time = QTime.currentTime()
print(time.toString())

# 현재 날짜와 시간 출력하기
datetime = QDateTime.currentDateTime()
print(datetime.toString())

# 날짜와 시간 형식 설정하기
datetime = QDateTime.currentDateTime()
print(datetime.toString('d.M.yy hh:mm:ss'))
print(datetime.toString('dd.MM.yyyy, hh:mm:ss'))
print(datetime.toString(Qt.DefaultLocaleLongDate))
print(datetime.toString(Qt.DefaultLocaleShortDate))
