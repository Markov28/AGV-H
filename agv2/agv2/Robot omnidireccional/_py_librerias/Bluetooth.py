import bluetooth #pip install pybluez2
import time  #default
import numpy   #pip install numpy

def scan():
    print("\n Scnng Bluetooth devices")
    devices = bluetooth.discover_devices(lookup_names= True, lookup_class= True)
    number_of_devices = len(devices)
    print(number_of_devices, " devices found")

    for addr, name, devices_class in devices:
        #if(name == "HC-05"):
        print("\n Device: ")
        print("Device Name: %s " % (name))
        print("Device MAC address: %s " % (addr))
        print("\n")
        print("Device Class: %s " % (devices_class))
        print("\n")

    return
 
def connect (bd_addr):
    port = 1
    sock=bluetooth.BluetoothSocket()
    sock.settimeout(20)
    while(True):
        try:
            sock.connect((bd_addr, port))
            break
        except:
            print("Error en conexion....reintentando")
        time.sleep(1)

    return sock



def move(sock,comando,wm1,wm2,wm3,wm4,sentido_wm1,sentido_wm2,sentido_wm3,sentido_wm4):
    #Información para el robot
    sock.send(comando.encode())
    # sock.send(numpy.int16(wm1))
    # sock.send(numpy.int16(wm2))
    # sock.send(numpy.int16(wm3))
    # sock.send(numpy.int16(wm4))
    #sock.send(numpy.int16(sentido_wm1))
    #sock.send(numpy.int16(sentido_wm2))
    #sock.send(numpy.int16(sentido_wm3))
    #sock.send(numpy.int16(sentido_wm4))
    # print("wm1="+str(wm1)+" wm2="+str(wm2)+" wm3="+str(wm3)+" wm4="+str(wm4)) 
    # print("sentido_wm1="+str(sentido_wm1)+" sentido_wm2="+str(sentido_wm2)+" sentido_wm3="+str(sentido_wm3)+" sentido_wm4="+str(sentido_wm4))
    print("letra: ",comando)
def move_agv(sock,dato):
    #Información para el robot
    sock.send(dato.encode())


def move_demo(sock):
    #Información para el robot
    sock.send('H'.encode())
    sock.send(numpy.int16(100))
    sock.send(numpy.int16(100))
    time.sleep(3)
    sock.send('H'.encode())
    sock.send(numpy.int16(0))
    sock.send(numpy.int16(0))
    time.sleep(3)
    sock.send('H'.encode())
    sock.send(numpy.int16(-100))
    sock.send(numpy.int16(-100))
    time.sleep(3)
    sock.send('H'.encode())
    sock.send(numpy.int16(0))
    sock.send(numpy.int16(0))
    time.sleep(3)

def disconnect(sock):
    sock.close()

# EJEMPLO
# scan()
#robot1=connect("98:D3:71:F6:63:9C") e0:5a:1b:75:74:4c
#move(robot1,100,100)
#disconnect(robot1)