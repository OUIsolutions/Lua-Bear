local luabear  = require("release/luaBear/luaBear")
local response = luabear.fetch({url="https://example.com/"})
print(response.read_body())