-- Import the library
local luabear = require("release/luaBear/luaBear")

-- Make a simple GET request
local response = luabear.fetch({url = "https://example.com/",http_version = "1.1"})

-- Check status code
print("Status code:", response.status_code)

-- Print response headers
for header_name, header_value in pairs(response.headers) do
    print(header_name .. ": " .. header_value)
end

-- Print response body
print(response.read_body())