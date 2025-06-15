bear = package.loadlib("./bear.so","load_lua_bear")()

local response = bear.fetch({url="https://example.com/"})
print(response.read_body())