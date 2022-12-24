from datetime import date
from datetime import datetime

class Todays_date_time:
    def __init__(self) -> None:
        todays_date = date.today()
        now = datetime.now()
        self.weekday = todays_date.weekday()
        self.day = todays_date.day
        self.month = todays_date.month
        self.year = todays_date.year
        self.date= self.getDate()
        self.hour = now.hour
        self.min = now.minute
        self.sec = now.second
        self.micro = now.microsecond

    def getTime(self):
        return self._str2Dig(self.hour)+":"+self._str2Dig(self.min)+":"+self._str2Dig(self.sec)+"."+str(self.micro)

    def _str2Dig(self,number:int)->str:
        if number < 10:
            return "0"+str(number)
        else:
            return str(number)

    def getDate(self):
        return self.getStrWeekday(self.weekday)+", "+self._str2Dig(self.day)+"/"+self._str2Dig(self.month)+"/"+str(self.year)

    def getStrWeekday(self,number)->str:
        str_wd = ["lunes","martes","miercoles","jueves","vierners","sabado","domingo"]
        return str_wd[number]

    def serial_msg_date(self):
        return f"D:{self.year};{self.month};{self.day};{self.weekday}"
        
    def serial_msg_time(self):
        return f"T:{self.hour};{self.min};{self.sec}"
