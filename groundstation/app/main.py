from PyQt5.QtWidgets import QApplication, QLabel, QWidget
import sys
import serial
import struct
import serial.tools.list_ports
ports = serial.tools.list_ports.comports()
for port in ports:
    print(port.device)
transceiver = serial.Serial(r'\\.\COM10', baudrate=115200, timeout=1)
app = QApplication(sys.argv)



window = QWidget()
window.setWindowTitle("My PyQt App")
window.setGeometry(100, 100, 400, 400)
label = QLabel('<center>no data</center>', parent=window)
window.show()
sys.exit(app.exec_())
STRUCT_FORMAT = '<i'  # Little-endian: int
STRUCT_SIZE = struct.calcsize(STRUCT_FORMAT)
while 1:
    data = transceiver.read(STRUCT_SIZE)
    if len(data) == STRUCT_SIZE:
        error, = struct.unpack(STRUCT_FORMAT, data)
        label.setText(str(error))