import requests # <-- To query Weather API Server
import json     # <-- To parse Weather JSON Data

apiAppid = "appid=" + "openWeatherAPInumber"

class Weather:
    city:str
    data:dict
    def __init__(self,city) -> None:
        self.city = city
        self.__basic_configuration()

    def __basic_configuration(self)->None:
        weatherCity = "&q=" + self.city
        # Weather Reporting Metrics Unit
        # "&units=imperial" # <-- To get Temperature Unit in Farenheit
        # "&units=metric" # <-- To get Temperature Unit in Celcius
        weatherUnit = "&units=metric"
        # Finally to build the URL & query API
        weatherApiurl = "http://api.openweathermap.org/data/2.5/weather?"
        weatherApiurl = weatherApiurl + apiAppid + weatherCity + weatherUnit
        response = requests.get(weatherApiurl) 
        self.data = response.json()

    def isSucessful(self)->bool:
        return self.data["cod"] == 200

    def getAllData(self)->dict:
        return self.data

    def getTemp(self)->float:
        if(self.isSucessful()):
            return self.data["main"]["temp"]
        else:
            return None
    
    def getMaxTemp(self)->float:
        if(self.isSucessful()):
            return self.data["main"]["temp_max"]
        else:
            return None

    def getMinTemp(self)->float:
        if(self.isSucessful()):
            return self.data["main"]["temp_min"]
        else:
            return None

    def getWeather(self)->str:
        if(self.isSucessful()):
            return str(self.getTemp())+"°C ("+str(self.getMaxTemp())+"°C / "+str(self.getMinTemp())+"°C)"
        else:
            return None

    def serial_msg(self):
        temp = self.getTemp()
        min = self.getMinTemp()
        max = self.getMaxTemp()
        return f"W:{temp};{min};{max}"
