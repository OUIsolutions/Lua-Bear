---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3001/",
    method="POST",
    body="Hello, LuaBear!",
})
print(response.read_body())