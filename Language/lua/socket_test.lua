require "socket"

function DownLoad()
   local tempConnect = assert(socket.connect(host,80))
   local count = 0
   tempConnect:send("GET " .. file .. "HTTP/1.0\r\n\r\n")
   while true do
      local s, status, partial = receive(tempConnect)
      count = count + #(s or partial)
      if status == "closed" then break end      
   end
   tempConnect:close()
   print(file.count)
end

DownLoad()