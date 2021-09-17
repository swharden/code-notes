"""
This Python3 script scans the local network and lists all IPs that respond to ping.
"""
import multiprocessing
import subprocess


def ping(ip):
    p = subprocess.Popen(["ping", "-n", "1", ip], stdout=subprocess.PIPE)
    response = p.communicate()[0].decode()
    if not 'unreachable' in response: # customize according to your OS
        print(ip)


if __name__ == '__main__':
    for i in range(256):
        multiprocessing.Process(target=ping, args=[f"192.168.1.{i}"]).start()
