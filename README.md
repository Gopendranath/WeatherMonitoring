# problems solving
Remote area weather monitoring
we don't have to rellay in other's weather monitoring system
detailed weather analysis of a perticular altitude

# WeatherMonitoring
A weather monitoring system that can provide real time weather data and altitude of your location. To perform such monitoring we have used LoRa 433Mhz module for remote area communication. It uses CSS or FDM communication technology. it can send the data without using any internet or any cell tower or any satellite upto 12km. Arduino Uno will collect all weather data in remote area and sends through Lora module. After receiving the data in esp32 it shows the data in locally hosted webserver in esp32.

# Saving the data online
After collecting the data in esp32 we sent the data to the google sheet to store the data. To save the data we have used https request. We have send the data through post request. In google sheet appscript console we have created a web app for webhook service. there will be a Code.gs file. in this file there will be doget function and to collect the data we will pass a parameter called e. in this doget function we will collect all the data that comes through querry parameter. And there will be save_data function for saving the data to the google sheet.

# Viewing in the website
After saving the data we will show table in website to access anywhere in the world. To show the data in web site we have used SheetDB api for fetching. There will be a get request for all columns.

# Processing the data in local computer or in the cloud computer
We can get the data from the sheet by using the sheet id. After getting all the data we use pandas library for processing and plotting the data.
by this we can get the detailed analysis of the weather

# future Scope
we can use machine learning for weather forcasting. we can use solar to power the modules.
