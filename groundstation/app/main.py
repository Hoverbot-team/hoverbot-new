from PyQt5.QtWidgets import QApplication, QLabel, QWidget
import sys
import serial
import struct
import serial.tools.list_ports
ports = serial.tools.list_ports.comports()
for port in ports:
    print(port.device)
transceiver = serial.Serial('COM256', baudrate=115200, timeout=1)
app = QApplication(sys.argv)

STRUCT_FORMAT = '<i'  # Little-endian: int
STRUCT_SIZE = struct.calcsize(STRUCT_FORMAT)

window = QWidget()
window.setWindowTitle("My PyQt App")
window.setGeometry(100, 100, 400, 400)
label = QLabel('<center>no data</center>', parent=window)

data = transceiver.read(STRUCT_SIZE)
if len(data) == STRUCT_SIZE:
    error, = struct.unpack(STRUCT_FORMAT, data)
    label.setText(str(error))


window.show()
sys.exit(app.exec_())
