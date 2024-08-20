from _py_librerias import Bluetooth as Bt  # Bluetooth
from _py_librerias import Camera as cam  # Camara
import cv2  # OpenCV
import numpy as np 
import time 

def connect_robot(address):
    return Bt.connect(address)

def send_command(robot, command):
    Bt.move_agv(robot, str(command))
    print("Dato enviado: " + str(command))

def main():
    # INICIALIZACION ROBOT Y CAMARA
    robot_bt = connect_robot("00:22:12:02:6D:58")
    
    # Crear una ventana OpenCV
    cv2.namedWindow('Control')

    try:
        # PROGRAMA PRINCIPAL
        while True:
            # Mostrar una imagen vacía en la ventana de OpenCV
            cv2.imshow('Control', 255 * np.ones((100, 100, 3), np.uint8))
            
            k = cv2.waitKey(33)
            if k == 27:  # Presiona esc para salir
                break
            elif k == 32:  # Presiona space para detener
                bot = "f"
            elif k == 119:  # Presiona w para avanzar
                bot = "w"
            elif k == 115:  # Presiona s para ir atras
                bot = "s"
            elif k == 100:  # Presiona d para mover a la derecha
                bot = "d"
            elif k == 97:  # Presiona a para mover a la izquierda
                bot = "a"
            elif k == 113:  # Presiona q para rotar a la izquierda
                bot = "q"
            elif k == 101:  # Presiona e para rotar a la derecha
                bot = "e"
            else:
                bot = "f"  # Restablecer a 'f' si no se presiona ninguna tecla
            
            send_command(robot_bt, bot)
            time.sleep(1.75)
    finally:
        # FINALIZAR EL PROGRAMA
        send_command(robot_bt, "f")  # Detener el robot
        Bt.disconnect(robot_bt)  # Desconectar Bluetooth
        cv2.destroyAllWindows()  # Cerrar todas las ventanas de OpenCV

if __name__ == "__main__":
    main()
