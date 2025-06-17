# LuaBear: HTTP Client Library for Lua

LuaBear is a powerful and easy-to-use HTTP client library for Lua, designed to make HTTP requests and handle responses with a simple and intuitive API. It supports sending and receiving data in various formats, including JSON, binary, and file streams, and allows for custom headers and flexible request options.

## Features
- Simple HTTP(S) requests (GET, POST, etc.)
- Read response as string, chunked, or JSON
- Send data as string, JSON, binary, or file stream
- Custom request headers
- Easy integration with Lua projects

## Installation
To install the lib, just download the lib [Lib Download](https://github.com/OUIsolutions/Lua-Bear/releases/download/0.1.0/luaBear.zip)
in the root of your project, and run with:

```lua
local luabear  = require("luaBear.luaBear")

```



#### Installation from Command
if you prefer to install with a command, just type:
```shell
 curl -L -o Lua-Bear.zip https://github.com/OUIsolutions/Lua-Bear/releases/download/0.1.0/luaBear.zip && unzip Lua-Bear.zip && rm Lua-Bear.zip
```


#### Build from scratch

For building from scratch you need to have Darwin installed on your machine. To install Darwin:
```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.020/darwin.out -o darwin.out && chmod +x darwin.out &&  sudo  mv darwin.out /usr/bin/darwin
```

You'll also need Docker (default) or Podman installed on your system.

Then you can build the project in the root directory of the project:

Using Docker (default):
```bash
darwin run_blueprint build/  --mode folder build_release
```

Using Podman:
```bash
darwin run_blueprint build/  --mode folder build_release --provider podman
```


## Basic Usage

### Simple GET Request
```lua
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({url="https://example.com/"})

print("status code:", response.status_code)
for header_name, header_value in pairs(response.headers) do
    print(header_name .. ":" .. header_value)
end
print(response.read_body())
```

### Reading Response in Chunks
```lua
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({url="https://example.com/"})
while true do
    local chunk = response.read_body_chunk(1024)
    if not chunk then break end
    print(chunk)
end
```

### Reading JSON Response
```lua
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({url="https://jsonplaceholder.typicode.com/todos/1"})
local body = response.read_body_json()
print(body["userId"], body["title"], body["completed"])
```

### Sending String Data (POST)
```lua
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3001/",
    method="POST",
    body="Hello, LuaBear!",
})
print(response.read_body())
```

### Sending JSON Data (POST)
```lua
local luabear  = require("luaBear.luaBear")
luabear.nil_code = "nil" -- set the nil code to avoid errors with nil values
local response = luabear.fetch({
    url="http://localhost:3001/",
    method="POST",
    body={username="LuaBear", password="secret", email="nil"},
})
print(response.read_body())
```

### Sending Binary Data (POST)
```lua
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3000/",
    method="POST",
    body=io.open("test.png", "rb"):read("*a"),
})
print(response.read_body())
```

### Sending File Stream (POST)
```lua
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3000/",
    method="POST",
    body=luabear.file_stream("test.png")
})
print(response.read_body())
```

### Setting Custom Headers
```lua
local luabear  = require("luaBear.luaBear")
local response = luabear.fetch({
    url="http://localhost:3001/",
    method="POST",
    headers={
        username="your username",
        password="your password"
    }
})
print(response.read_body())
```

## API Reference

### `luabear.fetch(options)`
Performs an HTTP request.
- `options.url` (string): The URL to request (required)
- `options.method` (string): HTTP method (default: "GET")
- `options.body` (string/table/stream): Request body (optional)
- `options.headers` (table): Custom headers (optional)

Returns a `response` object:
- `response.status_code`: HTTP status code
- `response.headers`: Table of response headers
- `response.read_body()`: Reads the full response body as a string
- `response.read_body_chunk(size)`: Reads the response body in chunks of `size` bytes
- `response.read_body_json()`: Parses the response body as JSON and returns a Lua table

### `luabear.file_stream(filename)`
Returns a file stream object for use as a request body (for large/binary files).

### `luabear.nil_code`
Set this to a string to represent `nil` values in JSON encoding (useful for APIs that require explicit nulls).

## Examples
See the `examples/` directory for more usage examples:
- `read_all.lua`: Basic GET request and print all response
- `read_chunk.lua`: Read response in chunks
- `read_json.lua`: Parse JSON response
- `sending_str.lua`: Send string data
- `sending_json.lua`: Send JSON data
- `sending_binary.lua`: Send binary data
- `sending_file.lua`: Send file stream
- `setting_headers.lua`: Custom headers

## License
See [LICENSE](/LICENSE).
