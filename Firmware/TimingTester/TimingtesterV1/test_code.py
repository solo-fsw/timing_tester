from importlib import import_module


import serial 


# Create serial device
# 
ser = serial.Serial()

        

# Configure port
ser.port = 'COM4'
ser.baudrate = 115200
ser.bytesize = 8
ser.parity = 'N'
ser.stopbits = 1
ser.timeout = 2
        
# Open serial device
ser.open()




# this is the error I got at some point: 
# SerialException: could not open port 'COM4': PermissionError(13, 'Access is denied.', None, 5)



MYINFO =80
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

def get_port(device_name):
    # Finds the com port address of UsbParMarker or SignalGenerator
    # Note, to find the com port address of the SignalGenerator, the signal_generator module is necessary
    # and to find the com port address of the UsbParMarker, the usb_par_marker module is necessary

    # Input: device_name = 'UsbParMarker' or 'SignalGenerator'
    # Output: com_ports = the com port address(es) to which the serial device is connected.

    # Get serial port addresses
    import serial.tools.list_ports
    ports = serial.tools.list_ports.comports()

    # init:
    port_names = []
    com_ports = []

    # Loop through ports and collect port names:
    for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))
        port_names.append(port)

    # when devices are found, get their actual name
    if len(port_names) != 0:

        if device_name == 'UsbParMarker':

            from usb_par_marker import send_command

            # loop through ports
            for port in port_names:

                # Open port with baudrate of 4800 to be able to get the name of the device:
                ser_device = init_serial_device(port, 4800, 1)

                if type(ser_device) == str:
                    continue

                # Ping the device:
                data = send_command(ser_device, 'P')
                print('data: ' + str(data))

                # Check if UsbParMarker is found:
                if 'UsbParMarker' in data:
                    com_ports.append(port)
                    print('UsbParMarker found')

                # close port
                close_serial_device(ser_device)
                
# Create serial device


# Create serial device
# 

# RESETTESTER MYINFO
    ser.reset_input_buffer()
    ser.reset_output_buffer()
  

# IMPORT PAR MARKER 


def send_command(ser, command):

    if ser_device.port == 'FAKECOM':
        decoded_data = 'ERROR: no data, FAKECOM used.'

    else:
        if type(command) == str:
            ser_device.write(command.encode()) 
            data = ser_device.readline()
            decoded_data = data.decode('utf-8')
            return decoded_data
        elif type(command) == int:
            ser_device.write(bytearray([command]))



# STARTDISPLAYTEST
ser.write(int(STARTDISPLAYTEST).to_bytes(1, 'big'))
print(response)
print (ser)
print # ebCrLf


# DUMP DISPLAYDATA








# Close ser device


def close_serial_device(ser_device):

    ser_device.close()










