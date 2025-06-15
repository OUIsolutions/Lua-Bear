---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({url="https://example.com/"})
local body = response.read_body()
print(body)