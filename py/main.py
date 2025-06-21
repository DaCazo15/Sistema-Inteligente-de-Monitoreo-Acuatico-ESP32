from src.ruta.ruta import localizacion
from src.servidor.server import *
from config.config import *
import serial
import time
import random

if __name__ == "__main__":
    while True:
        locationA = get_last_location()
        if locationA is None:
            print("No se pudo obtener la ubicación de Supabase")
        else:
            locationB = locationA + random.uniform(0.0000346, 0.000746)
            resultado = localizacion(locationA, locationB)
            # print(resultado)
            
            time.sleep(3)
            rest = insert_new_gps(locationA, locationB)
            print(rest)

            if rest.data == 201:
                print("Nueva ubicación GPS insertada correctamente.")

            # Enviar por puerto serie
            # serial_port = PUERTO_SERIAL
            # if serial_port is None:
            #     print("No se encontró un puerto serie disponible (excepto COM3).")
            # else:
            #     try:
            #         with serial.Serial(serial_port, BAUDRATE, timeout=0.5) as ser:
            #             time.sleep(0.6)
            #             ser.write((resultado + "\n").encode('utf-8')) 
            #     except Exception as e:
            #         print(f"Error enviando por serial: {e}")