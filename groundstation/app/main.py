from PyQt5.QtWidgets import *
import sys
import serial
import struct
import serial.tools.list_ports
UARTDevices = []
def selectionChanged(index):
    try:
        transceiver = serial.Serial(rf'\\.\{UARTDevices[index]}', baudrate=115200, timeout=1)
        print("uart initialised")
    except:
        print("init failed")



ports = serial.tools.list_ports.comports()
transceiver = 0

app = QApplication(sys.argv)
window = QWidget()
window.setWindowTitle("My PyQt App")
window.setGeometry(100, 100, 600, 400)
label = QLabel('<center>no data</center>', parent=window)

#create selector

for port in ports:
    UARTDevices.append(port.device)
    print(UARTDevices)

selcector = QComboBox(parent=window)
selcector.setGeometry(0,0,60,30)
selcector.addItems(UARTDevices)
selcector.currentIndexChanged.connect(selectionChanged)
window.show()


# UART begin

sys.exit(app.exec_())
STRUCT_FORMAT = '<i'  # Little-endian: int
STRUCT_SIZE = struct.calcsize(STRUCT_FORMAT)
while 1:
    data = transceiver.read(STRUCT_SIZE)
    if len(data) == STRUCT_SIZE:
        error, = struct.unpack(STRUCT_FORMAT, data)
        label.setText(str(error))



