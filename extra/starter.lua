local info = debug.getinfo(1, "S")
local path = info.source:match("@(.*/)") or ""

local lib_path = ''

if os.getenv("HOME") then
    lib_path = path .. "luaBear.so"
else
    lib_path = path .. "luaBear.dll"
end

local load_lua = package.loadlib(lib_path, "load_lua_bear")

---@type LuaBearModule
local lib = load_lua()

return lib
