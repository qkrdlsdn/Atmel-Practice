from motorCtrl import *
import serial

ser = serial.Serial(
    port='COM3',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

def signals(self):
    self.sendBtn.clicked.connect(self.motor)
    
def motor(self):
    speed = self.text.toPlainText()
    
    msg = "".join['\x02',speed,'\x03']
    ser.write(bytes(msg.encode()))
    self.text.clear()
    
Ui_Form.signals = signals
Ui_Form.motor = motor
    
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_Form()
    ui.setupUi(MainWindow)
    ui.signals()
    MainWindow.show()
    sys.exit(app.exec_())
    