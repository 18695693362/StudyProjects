--print("HelloWorld!")

function Send(x)
   coroutine.yield(x)
end

function Receive()
   local status, value = coroutine.resume(Producer)
   return value
end   

--[[
function Producer()
   while true do
      local x = io.read()
      Send(x)
   end      
end
]]--

Producer = coroutine.create(function ()
			       while true do
				  local x = io.read()
				  Send(x)
			       end
			    end)


function Consumer()
   while true do
      local x = Receive()
      io.write(x,"\n")
   end
end

function Permgen(a,n)
   n = n or #a
   if n <= 1 then
      PrintResult(a)
   else
      for i=1,n do
	 a[n], a[i] = a[i], a[n]
	 Permgen(a,n-1)
	 a[n], a[i] = a[i], a[n]
      end
   end
end

function PrintResult(a)
   for i=1, #a do
      io.write(a[i]," ")
   end
   io.write("\n")
end

--Permgen({1,2,3,4,5,6,7})
entry = {["a"] = 12, b = 13}
print(entry.a)
print(entry.b)
print(entry["a"])
set = {"hello","world"}
print(set[1])

a = "abcdef"

for i=1,#a do
   print(string.sub(a,i,i))
end