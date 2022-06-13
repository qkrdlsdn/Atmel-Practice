from ballUI import *
import serial
import threading

ser = serial.Serial(
    port='COM4',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

def counter():
    cnt = 0
    
    while True:
        rxdata = ser.readline().decode('utf-8')
        if rxdata:
            print(rxdata)
            cnt = cnt + 1
            ui.count.setText(str(cnt))
    
Ui_Form.counter = counter;

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_Form()
    ui.setupUi(MainWindow)
    
    dataThread = threading.Thread(target=counter)
    dataThread.daemon = True
    dataThread.start()
    
    MainWindow.show()
    sys.exit(app.exec_())