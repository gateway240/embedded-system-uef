# This is supposed to be very simple data read script to work as basis for further developement for more specific needs.
# If need for help, do email aaro.heikkinen@uef.fi or come by my current office
## --- ##
# To read data from arduino first locate with device it. Use command inside brackets (dmesg -w) to read print kernel ring buffer
# -> unplug and plug your arduino and it should see text apearing and last line like
# ttyACM0: USB ACM device
# where the ttyACM0 is the device. Change your device to the script /dev/your_device
# When enough data you can exit Ctrl+C

stty -F /dev/your_device 9600 -icrnl      # Configures the file, -icrnl makes is that there are no empty lines between
date > arduino_data.txt                   # Make new file named arduino_data.txt and add date to it
cat /dev/your_device >> arduino_data.txt  # Concatenate files and append them to arduino_data.txt
