import threading
import time
from communicator import Communicator
from weather import Weather
from todays_date_time import Todays_date_time

class Updater:
    def __init__(self, config:dict =  {"city" : "Madrid", "secs_to_update" : 2}) -> None:
        self.communicator:Communicator = Communicator()
        self.city = config["city"]
        self.secs_to_update = config["secs_to_update"]
        self.update()
        time.sleep(0.2)
        self.update()
        time.sleep(0.2)
        self.update()
    
    def get_data(self) -> tuple[Weather, Todays_date_time]:
        weather:Weather = Weather(self.city)
        date_time:Todays_date_time = Todays_date_time()
        return weather, date_time

    def send_msg(self,msg):
        return self.communicator.write_read(msg)

    def update(self):
        threading.Timer(self.secs_to_update, self.update).start()
        data = self.get_data()
        weather = 0
        date_time = 1
        print(self.send_msg(data[weather].serial_msg()))
        print(self.send_msg(data[date_time].serial_msg_date()))
        print(self.send_msg(data[date_time].serial_msg_time()))

config:dict = {"city" : "Carabanchel", "secs_to_update" : 600}
Updater(config)