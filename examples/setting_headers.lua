---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3001/",
    method="POST",
    headers={
        username="your username",
        password ="your password"
    }
})
print(response.read_body())