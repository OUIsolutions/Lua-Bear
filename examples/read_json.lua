---@type LuaBearModule
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({url="https://jsonplaceholder.typicode.com/todos/1"})
local body = response.read_body_json()
local user_id = body["userId"]
local title = body["title"]
local completed = body["completed"]
print("userId",user_id)
print("title",title)
print("completed",completed)