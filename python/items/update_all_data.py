import threading
import time

from weather import Weather
from todays_date_time import Todays_date_time
from communicator import Communicator

communicator = Communicator()

def update_all_data():
    threading.Timer(9.7, update_all_data).start()
    if(not communicator.isOpen()):
        communicator.open()
    weather = Weather("Carabanchel")
    dateTime = Todays_date_time()

    msg = dateTime.serial_msg_date()
    print(communicator.write_read(msg))
    time.sleep(0.1)
    
    msg = dateTime.serial_msg_date()
    print(communicator.write_read(msg))
    time.sleep(0.1)

    msg = dateTime.serial_msg_time()
    print(communicator.write_read(msg))
    time.sleep(0.1)

    msg = weather.serial_msg()
    print(communicator.write_read(msg))
    #communicator.close()
update_all_data()
