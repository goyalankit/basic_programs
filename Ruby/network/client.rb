require 'socket'      # Sockets are in standard library

hostname = 'localhost'
port = 2000

loop{
    s = TCPSocket.open(hostname, port)
    inp = gets
    s.puts(inp)

    while line = s.gets   # Read lines from the socket
        puts line.chop      # And print with platform line terminator
    end
    s.close
}
