require 'rubygems'
require 'serialport'

s = SerialPort.new("/dev/ttyACM0", baudrate: 9600)

(0..99999999).each { |n|  s.write("#{n}\r\n") ; sleep(0.01) }