import serial.tools.list_ports
import win32api
import win32con
import device
import cv2
import numpy as np
import time


# buttons dimensions (y1,y2,x1,x2)
buttonUP    = (757, 818, 312, 373)
buttonDOWN  = (899, 960, 312, 373)
buttonRIGHT = (828, 889, 398, 459)
buttonLEFT  = (828, 889, 223, 284)
buttonA     = (828, 889, 609, 670)
buttonB     = (828, 889, 724, 785)
buttonX     = (828, 889, 839, 900)
buttonY     = (828, 889, 954, 1015)
buttonPLUS  = (828, 889, 1069, 1130)

# Buttons list of tuples of pixels, names and status
buttons      = (buttonUP, buttonDOWN, buttonRIGHT, buttonLEFT, buttonA, buttonB, buttonX, buttonY, buttonPLUS)
button_names = ('Button UP', 'Button DOWN', 'Button RIGHT', 'Button LEFT', 'Button A', 'Button B', 'Button X', 'Button Y', 'Button PLUS')
pressed      = [False, False, False, False, False, False, False, False, False]
myCommand    = (b'U', b'D', b'R', b'L', b'A', b'B', b'X', b'Y', b'P')

#Define controller overlay when no button is pressed
overlay = cv2.imread("Recursos/Released.jpg", cv2.IMREAD_UNCHANGED)

#Define command to send to Arduino
arduino = ''


def echo_arduino(myPort):
    
    with serial.Serial(port=myPort, baudrate=9600, timeout=0.1) as arduino:
        time.sleep(2)
        
        for a in range(4):
            print('Searching for controller (attempt #' + str(a) + ')')
            arduino.write(b'9')
            time.sleep(0.05)
            response = arduino.readline()
            # print('response: ' + response.decode("utf-8"))
            if response.decode("utf-8") == 'ArduinoController':
                print('Arduino controller found!')
                print('Establishing connection...')
                return True

        return False


def detect_controller():
    
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        print('Cheking: ' + str(p[0]))
        if echo_arduino(p[0]) == True:
            return p[0]
    
    return False
    

def choose_capturecard():

    # print OpenCV version
    print("OpenCV version: " + cv2.__version__)

    # Get camera list
    device_list = device.getDeviceList()
    etiqueta = 0

    for name in device_list:
        print(str(etiqueta) + ': ' + name)
        etiqueta += 1

    recuento = etiqueta - 1

    if recuento < 0:
        print("No device is connected")
        return

    mensaje = "Select a camera (0 to " + str(recuento) + "): "
    try:
        capture_number = int(input(mensaje))
    except Exception:
        print("It's not a number!")
        print()
        return choose_capturecard()

    if (capture_number > recuento) or capture_number < 0:
        print("Invalid number! Retry!")
        print()
        return choose_capturecard()

    return capture_number


# function that handles the mousclicks
def process_click(event, x, y,flags, params):
    global buttons
    global buttons_names
    global pressed
    global overlay
    global arduino
    
    # check if the click is within the dimensions of the buttonUP
    if event == cv2.EVENT_MOUSEMOVE:
        win32api.SetCursor(win32api.LoadCursor(0, win32con.IDC_HAND))
        for a in buttons:
            if y > a[0] and y < a[1] and x > a[2] and x < a[3] and pressed[buttons.index(a)] == False:
                pressed[buttons.index(a)] = True
                arduino.write(myCommand[buttons.index(a)])
                overlay = cv2.imread('Recursos/' + button_names[buttons.index(a)] + ".jpg", cv2.IMREAD_UNCHANGED)
                print(button_names[buttons.index(a)] + ' pressed!')
            elif (y < a[0] or y > a[1] or x < a[2] or x > a[3]) and pressed[buttons.index(a)] == True:
                pressed[buttons.index(a)] = False
                overlay = cv2.imread("Recursos/Released.jpg", cv2.IMREAD_UNCHANGED)
                print(button_names[buttons.index(a)] + ' released!')



if __name__ == "__main__":

    arduinoController = detect_controller()

    if arduinoController != False:
    
        with serial.Serial(port=arduinoController, baudrate=9600, timeout=0.1) as arduino:
            time.sleep(2)
            
            for a in range(4):
                arduino.write(b'9')
                time.sleep(0.05)
                response = arduino.readline()
                
                if response.decode("utf-8") == 'ArduinoController':
                    print('connection established!')
                    print()
                    arduino.write(b'A')
                    time.sleep(0.5)
                    arduino.write(b'A')
                    break
                else:
                    print('Failure to establish connection')
                    print()

            # Preguntar por capturadora
            capture = cv2.VideoCapture(choose_capturecard(), cv2.CAP_DSHOW)
            
            #Definir ventana, callback de ventana y posicion inicial de ventana
            cv2.namedWindow("Adapted Controller")
            cv2.setMouseCallback("Adapted Controller",process_click)
            cv2.moveWindow("Adapted Controller",0 , 0)
            
            while True:
                # Leer la capturadora
                success, frame = capture.read()
                
                frame_resized = cv2.resize(frame, (1280, 720))
                
                vertical = np.concatenate((frame_resized, overlay), axis=0)
                
                cv2.imshow("Adapted Controller", vertical)  # SHOW HIDE VGC INFO window
                
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    capture.release()
                    cv2.destroyAllWindows()
                    break
 
 
 
    else:
        print('No arduino controller found. Exiting the program.')