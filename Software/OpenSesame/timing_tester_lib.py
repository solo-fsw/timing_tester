# -*- coding: utf-8 -*-
"""
Created on Tue Apr 19 14:05:10 2022

@author: matsulevitsa
"""

import serial 
import re
import pandas as pd


#%% Constants:

# MYINFO returns a string with the spider's version and serial number.
MYINFO =80

# 
PING =81
RESETTESTER =90
TESTINGFINISHED =91
DISPLAYTESTSETUP= 100
AUDIOTESTSETUP =101
SRBOXTESTSETUP = 102
MARKER =109
STARTDISPLAYTEST= 110
STARTAUDIOTEST= 111
STARTSRBOXTEST= 112
STOPTESTER= 115
DUMPDISPLAYDATA= 48
DUMPAUDIODATA= 151
DUMPSRBOXDATA= 152



#%% 





#%% Functions



def write_to_spider(ser, int_code, get_response = True):
    # Writes a code to the spider.
    
    ser.reset_input_buffer()
    #ser.reset_output_buffer()
    ser.write(int(int_code).to_bytes(1, 'big'))
    
    if get_response:
        response = ser.readall()
        response = response.decode("utf-8").replace('\r\n', '')
        return response
    
    
def get_test_data(ser, dump_code, label = 'blank', tablein = pd.DataFrame()):
    # Writes a code to the spider.
    
    
    response = write_to_spider(ser, dump_code, True)

    # For display, the response will be:
    #
    #   D;1;<interval in us>D;2;<interval in us>D;3;<interval in us>  ETC.
    response_list = re.findall("\w;(?P<index>\d+);(?P<interval>\d+)", response)
  
    

### CREATE A TABLE FROM THE LIST WITH 3 COLUMNS FOR ITERATION, DELAY, LABEL OF WHAT WAS TESTED

    # Transform the string into table (dataframe?)
    print(response_list)
    result_table = pd.DataFrame(response_list, columns =['Iteration', 'Delay'], dtype = float) 
   # result_table = result_table.append({'average_delay' : result_table["Delay"].mean()}, ignore_index = True)
  
    result_table['Label'] = label
    
    result_table_merged = pd.concat((tablein, result_table))
    print(result_table_merged)
   
    return result_table_merged
    

# TODO: Add descriptives for every label after the loops (mean of delay)
# get column delay; calculate sum, divide by iteration and get output as extra table?

#Create a DataFrame
 #   print(result_table["Delay"].mean())
    
 #   print(result_table["Delay"].std())
    
 #   print(result_table["Iteration"].count())
    
### AVERAGE VALUE OF DELAY AND SAVING THE RESULTS TO A CSV FILE 
# creating a main table that merges all of the result tables from the separate tests

# main_table = pd.DataFrame(get_test_data(ser, DUMPDISPLAYDATA))

#
 

          
        

def init_spider(com_port = 'COM4'):
    # Create serial device
    
    ser = serial.Serial()


    # Configure port
    ser.port = com_port
    ser.baudrate = 115200
    ser.bytesize = 8
    ser.parity = 'N'
    ser.stopbits = 1
    ser.timeout = 2
            
    # Open serial device
    ser.open()
    
    # Check it:
    response = write_to_spider(ser, PING, True)
    print(response)
    assert (response == 'pong'), "Device is not a spider."

    
    # On init, reset spider:
    write_to_spider(ser, RESETTESTER, False)
    
    response = write_to_spider(ser, MYINFO, True)
    print(response)
    
    
    return ser

