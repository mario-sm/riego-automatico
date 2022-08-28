#!/usr/bin/env python


import serial,time
import serial.tools.list_ports


if __name__ == '__main__':
    ports = list(serial.tools.list_ports.comports())
    port = None
    for p in ports:
        if p.manufacturer is not None and 'Arduino' in p.manufacturer:
            port = p.device

    print('Running. Press CTRL-C to exit.')
    with serial.Serial(port, 115200, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            time.sleep(2) #wait for arduino to answer

            try:
                while True:
                    time.sleep(0.1) #wait for arduino to answer

                    arduino.write(( 'read\r\n').encode())
                    
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0: 
                        answer=str(arduino.readline())
                        print("---> {}".format(answer))    
                        arduino.flushInput() #remove data after reading
                            
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")

    
        