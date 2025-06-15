

---@class BearProps
---@field url string
---@field method string | nil
---@field headers table<string, string> | nil
---@field body string | table | nil

---@class LuaBearFileStream


---@class LuaBearModule
---@field fetch fun(props:BearProps): BearResponse
---@field nil_code string
---@field file_stream fun(file_path:string,content_type:string | nil): LuaBearFileStream

---@class BearResponse
---@field status_code integer
---@field headers table<string, string>
---@field read_body fun(): string
---@field read_body_json fun(): table
---@field read_body_chunk fun(size:integer): string




local info = debug.getinfo(1, "S")
local path = info.source:match("@(.*/)") or ""

local lib_path = ''

if os.getenv("HOME") then
    lib_path = path.."luaBear.so"
else
    lib_path = path.."luaBear.dll"
end 

local load_lua = package.loadlib(lib_path, "load_lua_bear")

---@type LuaBearModule
local lib = load_lua()

return lib