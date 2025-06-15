---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
luabear.nil_code = "nil" --set the nil code to "nil" to avoid errors when reading nil values
local response = luabear.fetch({
    url="http://localhost:3001/",
    method="POST",
    body={username="LuaBear", password="secret",email="nil"},
})
print(response.read_body())