import serial.tools.list_ports

def puerto(exclude_port="COM3"):
    ports = list(serial.tools.list_ports.comports())
    for port in ports:
        if port.device != exclude_port:
            return port.device
    return None