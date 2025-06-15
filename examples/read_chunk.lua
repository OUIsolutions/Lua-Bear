---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({url="https://example.com/"})
while true  do 
    local chunk = response.read_body_chunk(1024)
    if not chunk then 
        break
    end
    print(chunk)
end 