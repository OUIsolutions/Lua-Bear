---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3000/",
    method="POST",
    body=luabear.file_stream("test.png")
})
print(response.read_body())