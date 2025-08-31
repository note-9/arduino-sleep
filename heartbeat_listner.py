import socket
import time
import os

UDP_IP = "0.0.0.0"
UDP_PORT = 12345
TIMEOUT = 300  # 5 minutes

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
sock.settimeout(TIMEOUT)

while True:
    try:
        data, addr = sock.recvfrom(1024)
        # Heartbeat received; continue
    except socket.timeout:
        os.system("systemctl suspend")
