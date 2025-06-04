from PyQt5.QtWidgets import QApplication, QLabel, QWidget
import sys

app = QApplication(sys.argv)

window = QWidget()
window.setWindowTitle("My PyQt App")
window.setGeometry(100, 100, 280, 80)

label = QLabel('<center>Hello, PyQt!</center>', parent=window)
window.show()

sys.exit(app.exec_())
