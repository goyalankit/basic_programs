require 'socket'                # Get sockets from stdlib

class Node
    def self.handle_request client
        p "handling requests now.."
        message = client.gets
        if(message.strip == "yes")
            client.puts "commit"
        else
            client.puts "abort"
        end
    end

    server = TCPServer.open(2000)   # Socket to listen on port 2000
    loop {                          # Servers run forever
        Thread.start(server.accept) do |client|
            client.puts(Time.now.ctime) # Send the time to the client
            Node.handle_request(client)
            client.close
        end
    }
end
