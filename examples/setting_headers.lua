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
local body = response.read_body()
print(body)