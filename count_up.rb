require 'rubygems'
require 'serialport'
require 'byebug'

@s = SerialPort.new("/dev/ttyACM0", baudrate: 9600)
sleep 2 # wait until the port is ready


def set_number(number)
  puts "n#{number}\r\n"
  @s.write("n#{number}\r\n")
end


def set_digits(number)
  n = 0
  number_string = number.to_s
  number_string.to_s.each_char do |c|
    digit = number_string.length - n -1
    @s.write("d#{digit}#{c}\n")
    n += 1
  end
end

set_digits("12s34s56")

#(0..99999999).each { |n|  s.write("#{n}\r\n") ; sleep(0.01) }

