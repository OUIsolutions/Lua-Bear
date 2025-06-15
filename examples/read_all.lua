---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({url="https://example.com/"})


print("status code:",response.status_code)
print("----------------------------headers------------------------------------")
for headder_name,headder_value in pairs(response.headers) do
    print(headder_name..":"..headder_value)
end

local body = response.read_body()
print("----------------------------body------------------------------------")
print(body)