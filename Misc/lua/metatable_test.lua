
print("nil metatable       ", getmetatable(nil))
print("boolean metatable   ", getmetatable(true))
print("number metatable    ", getmetatable(1))
--strMetaTable = getmetatable("hello")
--print("string metatable    ", getmetatable("world"))
--strMetaTable.__metatable = "not your business"
print("string metatable    ", getmetatable("hi"))
print("table metatable     ", getmetatable({}))
print("function metatable  ", getmetatable(print))
print("userdata metatable  ", getmetatable(io))
co = coroutine.create(function ()
			 print("hi")
		      end)
print("thread metatable    ", getmetatable(co))


Window= {}
Window.prototype = {x=0,y=0,width=100,height=100}
Window.mt = {}
function Window.new(o)
   setmetatable(o,Window.mt)
   return o
end

Window.mt.__index = function (table,key)
   return Window.prototype[key]
end

w = Window.new{x=12,y=13}
print("x->", w.x, " y->", w.y, " width->", w.width, " height->", w.height)