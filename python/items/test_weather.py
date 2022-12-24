# Current Weather Report for City
import requests # <-- To query Weather API Server
import json     # <-- To parse Weather JSON Data 

# Register with Openweathermap & Get APPID
apiAppid = "appid=" + "55d229f31cbfc917f38757d1c96974d6"

# Get City name from User
weatherCity = input("Get Weather For City : ")
weatherCity = "&q=" + weatherCity

# Weather Reporting Metrics Unit
# "&units=imperial" # <-- To get Temperature Unit in Farenheit
# "&units=metric" # <-- To get Temperature Unit in Celcius
weatherUnit = "&units=metric"

# Finally to build the URL & query API
weatherApiurl = "http://api.openweathermap.org/data/2.5/weather?"
weatherApiurl = weatherApiurl + apiAppid + weatherCity + weatherUnit
response = requests.get(weatherApiurl) 
weatherJsonData = response.json()

# Check Return Code from API Server & Proceed
if weatherJsonData["cod"] == "404": 
	print("Error Code   = " + weatherJsonData["cod"]) 
else:
   #if weatherJsonData["cod"] == "200":
    # Print Basic Weather Parameters
    print(weatherJsonData)
    print("Description  = " + weatherJsonData["weather"][0]["description"])
    print("Temperature   = " + str(weatherJsonData["main"]["temp"]))
    print("Pressure     = " + str(weatherJsonData["main"]["pressure"]))
    print("Humidity     = " + str(weatherJsonData["main"]["humidity"]))