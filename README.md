# LuaBear 🐻

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Lua Version](https://img.shields.io/badge/Lua-5.1%2B-blue.svg)](https://www.lua.org/)
[![Release](https://img.shields.io/github/v/release/OUIsolutions/Lua-Bear)](https://github.com/OUIsolutions/Lua-Bear/releases)
[![Downloads](https://img.shields.io/github/downloads/OUIsolutions/Lua-Bear/total)](https://github.com/OUIsolutions/Lua-Bear/releases)

> A simple, powerful HTTP client library for Lua

## 📋 Overview

LuaBear is a user-friendly HTTP client library that makes sending web requests in Lua simple and straightforward. Whether you're a beginner or experienced developer, LuaBear provides an easy way to interact with web services and APIs.

## ✨ Features

- ✅ **Simple HTTP/HTTPS requests** (GET, POST, PUT, DELETE, etc.)
- ✅ **Flexible response handling** - read as string, chunks, or JSON
- ✅ **Multiple data formats** - send text, JSON, binary data, or files
- ✅ **Custom headers** - set any HTTP headers you need
- ✅ **Beginner-friendly API** - intuitive interface for new users

## 🚀 Installation

### Option 1: Direct Download (Recommended for Beginners)

1. Download the library package:
   ```
   mkdir -p luabear
   curl -L -o luabear/luabear.lua https://github.com/OUIsolutions/Lua-Bear/releases/download/0.1.1/luaBear.lua
   curl -L -o luabear/luabear.so https://github.com/OUIsolutions/Lua-Bear/releases/download/0.1.1/luaBear.so
   ```

2. Unzip the package:
   ```
   unzip Lua-Bear.zip
   ```

3. Clean up (optional):
   ```
   rm Lua-Bear.zip
   ```

4. Use in your Lua project:
   ```lua
   local luabear = require("luaBear.luaBear")
   ```

### Option 2: Manual Download

1. Download the library from [GitHub Releases](https://github.com/OUIsolutions/Lua-Bear/releases/download/0.1.0/luaBear.zip)
2. Extract the ZIP file to your project directory
3. Import in your code:
   ```lua
   local luabear = require("luaBear.luaBear")
   ```

### Option 3: Build from Source

Prerequisites:
- Install Darwin build tool:
  ```
  curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.020/darwin.out -o darwin.out && chmod +x darwin.out && sudo mv darwin.out /usr/bin/darwin
  ```

Build steps:
1. Clone the repository
2. Navigate to the project directory
3. Run:
   ```
   darwin run_blueprint build/ --mode folder build_release
   ```

## 📚 Quick Start Guide

### Making a Simple GET Request

```lua
-- Import the library
local luabear = require("luaBear.luaBear")

-- Make a simple GET request
local response = luabear.fetch({url = "https://example.com/"})

-- Check status code
print("Status code:", response.status_code)

-- Print response headers
for header_name, header_value in pairs(response.headers) do
    print(header_name .. ": " .. header_value)
end

-- Print response body
print(response.read_body())
```

## 📖 Common Examples

### Reading a JSON Response

```lua
local luabear = require("luaBear.luaBear")
local response = luabear.fetch({url = "https://jsonplaceholder.typicode.com/todos/1"})
local data = response.read_body_json()

-- Access JSON data easily
print("User ID:", data.userId)
print("Title:", data.title)
print("Completed:", data.completed)
```

### Sending Form Data (POST)

```lua
local luabear = require("luaBear.luaBear")
local response = luabear.fetch({
    url = "https://httpbin.org/post",
    method = "POST",
    body = {
        username = "bearuser",
        password = "bearpassword"
    }
})
print(response.read_body())
```

### Uploading a File

```lua
local luabear = require("luaBear.luaBear")
local response = luabear.fetch({
    url = "https://httpbin.org/post",
    method = "POST",
    body = luabear.file_stream("test.png")
})
print(response.read_body())
```

## 📝 API Reference

### Main Functions

#### `luabear.fetch(options)`
Makes an HTTP request with the given options.

**Parameters:**
- `options.url` (string): Target URL (required)
- `options.method` (string): HTTP method like "GET", "POST" (default: "GET")
- `options.body` (string/table/stream): Request body data
- `options.headers` (table): Custom HTTP headers

**Returns:**
A response object with:
- `status_code`: HTTP status code (e.g., 200, 404)
- `headers`: Table of response headers
- `read_body()`: Returns full response as string
- `read_body_chunk(size)`: Returns response in chunks
- `read_body_json()`: Parses and returns JSON response as table

#### `luabear.file_stream(filename)`
Creates a file stream for uploading files.

**Parameters:**
- `filename` (string): Path to the file

**Returns:**
A file stream object to be used with `fetch()`

## 🧪 More Examples

Check the `examples/` directory for complete working examples:
- Basic requests: `read_all.lua`
- Chunked reading: `read_chunk.lua`
- JSON handling: `read_json.lua`, `sending_json.lua`
- Binary data: `sending_binary.lua`
- File uploads: `sending_file.lua`
- Custom headers: `setting_headers.lua`

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](/LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.
