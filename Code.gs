function doGet(e){
  Logger.log("--- doGet ---");
 
 var rainfall = "",
     ldr = "",
     temperature = "",
     humidity = "",
     pressure = "",
     altitude = "";
 
  try {
 
    // this helps during debuggin
    if (e == null){e={}; e.parameters = {rainfall:"00",ldr:"00",temperature:"00",humidity:"00",pressure:"00",altitude:"00"};}
 
    rainfall = e.parameters.rainfall;    // do change
    ldr = e.parameters.ldr;  // do change
    temperature = e.parameters.temperature;
    humidity = e.parameters.humidity;
    pressure = e.parameters.pressure;
    altitude = e.parameters.altitude;

 
    // save the data to spreadsheet
    save_data(rainfall, ldr, temperature, humidity, pressure, altitude);
 
 
    return ContentService.createTextOutput("Wrote:\n  rainfall: " + rainfall + "\n  ldr: " + ldr + "\n  temprature: " + temperature + "\n humidity: " + humidity + "\n pressure: " + pressure + "\n altutude: " + altitude);
 
  } catch(error) { 
    Logger.log(error);    
    return ContentService.createTextOutput("oops...." + error.message 
                                            + "\n" + new Date() 
                                            + "\nrainfall: " + rainfall +
                                            + "\nldr: " + ldr +
                                            + "\ntemprature: " + temperature +
                                            + "\nhumidity: " + humidity +
                                            + "\npressure: " + pressure +
                                            + "\naltitude: " + altitude);
  }  
}
 
// Method to save given data to a sheet
function save_data(rainfall, ldr, temperature, humidity, pressure, altitude){
  Logger.log("--- save_data ---"); 
 //AKfycbz3i4wbzK2pizNWFUfD2tlNYXaDm_ioxQkM7ybaGuzGdwNYy9VbnaNpubEhRF9LoxF8
 //https://script.google.com/macros/s/AKfycbz3i4wbzK2pizNWFUfD2tlNYXaDm_ioxQkM7ybaGuzGdwNYy9VbnaNpubEhRF9LoxF8/exec
 //https://script.google.com/macros/library/d/1UOIbeTYCoQyESJuBQEoLfGncDDlNpZEWf_QD_v81dq4t6wkPK3y0gsND/1
 
  try {
    var dateTime = new Date();
 
    // Paste the URL of the Google Sheets starting from https thru /edit
    // For e.g.: https://docs.google.com/..../edit 
    var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/158q0Rt9iFCW8032bc0lJBbTWbQvEtMZF8QxNyqfNYKQ/edit");
    var dataCollectorSheet = ss.getSheetByName("DataCollector");
 
 
    // Get last edited row from DataLogger sheet
    var row = dataCollectorSheet.getLastRow() + 1;
 
 
    // Start Populating the data
    dataCollectorSheet.getRange("A" + row).setValue(row -1); // ID
    dataCollectorSheet.getRange("B" + row).setValue(dateTime); // dateTime
    dataCollectorSheet.getRange("C" + row).setValue(rainfall); // rainFall
    dataCollectorSheet.getRange("D" + row).setValue(ldr); // ldr
    dataCollectorSheet.getRange("E" + row).setValue(temperature); //temprature
    dataCollectorSheet.getRange("F" + row).setValue(humidity); //humidity
    dataCollectorSheet.getRange("G" + row).setValue(pressure); //pressure
    dataCollectorSheet.getRange("H" + row).setValue(altitude); //altitude
 
 
    // Update summary sheet
    summarySheet.getRange("B1").setValue(dateTime); // Last modified date
    // summarySheet.getRange("B2").setValue(row - 1); // Count 
  }
 
  catch(error) {
    Logger.log(JSON.stringify(error));
  }
 
  Logger.log("--- save_data end---"); 
}
