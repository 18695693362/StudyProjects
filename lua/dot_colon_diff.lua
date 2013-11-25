GLuaObject = {}
GLuaObject.__index = GLuaObject

function GLuaObject:Create()
   local temp = {}
   setmetatable(temp,GLuaObject)
   return temp
end

function GLuaObject:PrintSelf()
   print(": -> ", self, "\n")
end

function GLuaObject.CreateEx()
   local temp = {}
   setmetatable(temp,GLuaObject)
   return temp
end

function GLuaObject.PrintSelfEx()
   print(". -> ",self, "\n")
end

print("GLuaObject -> ",GLuaObject, "\n")

temp1 = GLuaObject:Create()
temp1:PrintSelf()
temp1.PrintSelfEx()

temp2 = GLuaObject.CreateEx()
temp2:PrintSelf()
temp2.PrintSelfEx()
   
   