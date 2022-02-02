# -*- coding: utf-8 -*-
"""
Created on Thu Feb  3 02:19:06 2022

@author: stelt

Задание выполнил Артём Кирик для Панковой Дины Игоревны :)

Реализован модуль для использования асинхронного tcp сервера с логгированием в качестве
параллельного процесса в основной программе, может быть использован и сам по себе.

Общение с внешним миром через Pipe, дружит с telnet, тестирован с помощью PuTTY

Возможен запуск через терминал, например:
   python D:\python_projects\my_tcp_srv.py D:\python_projects\log.bin 192.168.0.5 10000

"""

import socket
import selectors
import multiprocessing as mp


def run_server(address,max_conn,log_fname,pipe):
    
    sel = selectors.DefaultSelector()
    
    def accept(sock):
        conn, addr = sock.accept()
        conn.setblocking(False)
        sel.register(conn, selectors.EVENT_READ, read)
        return None
    
    def read(conn):
        try:
            data = conn.recv(24)
        except:
            sel.unregister(conn)
            conn.close()
            return None
        if data:
            return data
        else:
            sel.unregister(conn)
            conn.close()
            return None
        
    def write_log(data,log_fname):
        if len(data) == 24 and data.decode()[-1] == '\r':
            with open(log_fname, 'ab') as f:
                f.write(data)
                
    sock = socket.socket()
    sock.bind(address)
    sock.listen(max_conn)
    sock.setblocking(False)
    sel.register(sock, selectors.EVENT_READ, accept)
    while True:
        events = sel.select()
        for key, _ in events:
            data = key.data(key.fileobj)
            if data:
                pipe.send(data)
                write_log(data,log_fname)

def group_filter(data, groupe_number):
    gg = int(data[-3:-1])
    if gg == groupe_number:
        return True
    else:
        return False

if __name__ == '__main__':
    
    import sys
        
    
    host = socket.gethostname()
    host_ip = socket.gethostbyname(host)
    server_address = (host_ip,10000)
    log_fname = 'log.bin' #пишет бинарный лог, всё равно всё в ascii
    
    try:
        log_fname = sys.argv[1]
    except:
        pass
    try:
        kek = (sys.argv[2],int(sys.argv[2]))
        server_address = kek
    except:
        pass
    
    parent, child = mp.Pipe()
    server_process=mp.Process(
        target = run_server,
        args=(
            server_address,
            100,
            log_fname,
            child
            )
        )
    server_process.start()
    
    try:
        while True:
            try:
                data = parent.recv()
            except KeyboardInterrupt:
                server_process.join()
                server_process.close()
                print("выключение сервера")
                exit()
            except:
                print('что-то сломалось...')
                pass
            if len(data) == 24 and data.decode()[-1] == '\r':    
                if group_filter(data,0):
                    sp_number, channel, time, groupe = data[:-1].decode().split(' ')
                    print('спортсмен, нагрудный номер {} прошёл отсечку {} в {}'.format(sp_number,channel,time[:-2]))
    except KeyboardInterrupt:
        server_process.join()
        server_process.close()
        print("выключение сервера")
        exit()


    
    

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        