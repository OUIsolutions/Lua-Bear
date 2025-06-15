---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3000/",
    method="POST",
    body=io.open("test.png", "rb"):read("*a"), -- Read the binary file
})
print(response.read_body())