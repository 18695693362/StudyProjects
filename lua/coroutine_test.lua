function Send(x)
   coroutine.yield(x)
end

function Receive(prod)
   local status, value = coroutine.resume(prod)
   return value
end

function Producer()
   return coroutine.create(function ()
			      while true do
				 local x = io.read()
				 Send(x)
			      end
			   end)
end

function Filter(prod)
   return coroutine.create(function ()
			      for line=1,math.huge do
				 local x = Receive(prod)
				 x = string.format("%5d %s", line, x)
				 Send(x)
			      end
			   end)
end

function Consumer(prod)
   while true do
      local x = Receive(prod)
      io.write(x,"\n")
   end
end

p = Producer()
f = Filter(p)
Consumer(f)