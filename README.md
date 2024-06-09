# WeatherMonitoring
A weather monitoring system that can provide real time weather data and altitude of your location. To perform such monitoring we have used LoRa 433Mhz module for remote area communication. It uses FDM communication technology

# Saving the data online
After collecting the data in esp32 we sent the data to the google sheet to save. To save the data we have used https request. We have send the data through post request. In google sheet appscript console we have created a web app for webhook service. there will be a Code.gs file. in this file there will be doget function and to collect the data we will pass a parameter called e. in this doget function we will collect all the data that comes through querry parameter. And there will be save_data function for saving the data to the google sheet.
