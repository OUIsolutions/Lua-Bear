---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3001/",
    method="POST",
    body={username="LuaBear", password="secret"},
})
print(response.read_body())