# -*- coding: utf-8 -*-
"""
Created on Thu Feb  3 03:30:56 2022

Задание выполнил Артём Кирик для Панковой Дины Игоревны :)

Мультипроцессорный клиент для теста сервера

Просто запустить и наблюдать ~100 секунд

@author: stelt
"""

#BBBBxNNxHH:MM:SS.zhqxGGCR 
#1234 22 11:11:11.111 00

import socket
import random
import time
import multiprocessing as mp

random.seed()

def create_msg(gr = None):
    number = str(random.randint(0,9999)).rjust(4,'0')
    channel = str(random.randint(0,99)).rjust(2,'0')
    hours = str(random.randint(0,23)).rjust(2,'0')
    minutes = str(random.randint(0,59)).rjust(2,'0')
    sec = str(random.randint(0,59)).rjust(2,'0')
    subsec= str(random.randint(0,999)).rjust(3,'0')
    if gr:
        if int(gr) < 100:
            group = str(gr).rjust(2,'0')
        else:
            group = '00'
    else:
        group = str(random.randint(0,1)).rjust(2,'0')
    return bytes(number+' '+channel+' '+hours+':'+minutes+':'+sec+'.'+subsec+' '+group+'\r','utf8')

def run_client(channel):
    host = socket.gethostname()
    host_ip = socket.gethostbyname(host)
    server_address = (host_ip,10000)
    
    try:
        while True:
            client = socket.socket()
            client.connect(server_address)
            client.send(create_msg(channel))
            client.close()
            time.sleep(random.uniform(1,3))
    except:
        try:
            client.close()
        except:
            pass
if __name__ == '__main__':
    clients = [mp.Process(target=run_client,args=(ch,)) for ch in range(15)]
    for client in clients:
        client.start()
            
    time.sleep(100)
    for client in clients:
        client.terminate()