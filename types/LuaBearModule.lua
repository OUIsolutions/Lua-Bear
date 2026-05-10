--- Properties passed to `fetch()` to configure an HTTP/HTTPS request.
---@class BearProps
---@field url string The target URL (http or https).
---@field method string | nil HTTP method (e.g. "GET", "POST"). Defaults to "GET".
---@field headers table<string, string> | nil Key-value pairs sent as request headers.
---@field body string | table | LuaBearFileStream | nil Request body. A table is serialised to JSON automatically. Use `file_stream()` to stream a file.
---@field http_version string | nil HTTP protocol version: "1.0" or "1.1". Defaults to the library default when omitted.

--- Opaque handle returned by `file_stream()`. Pass it as the `body` of a request to upload a file.
---@class LuaBearFileStream


---@class LuaBearModule
---@field fetch fun(props:BearProps): BearResponse Perform an HTTP/HTTPS request and return the response.
---@field nil_code string Sentinel string used by `read_body_json()` to represent JSON null values. Defaults to `"__null__"`.
---@field file_stream fun(file_path:string, content_type:string|nil): LuaBearFileStream Create a file-stream handle for uploading a file. `content_type` is inferred from the extension when omitted.

---@class BearResponse
---@field status_code integer HTTP status code returned by the server (e.g. 200, 404).
---@field headers table<string, string> Response headers as key-value pairs.
---@field read_body fun(): string Read the full response body as a (possibly binary) string.
---@field read_body_json fun(): table Parse the full response body as JSON and return a Lua table.
---@field read_body_chunk fun(size:integer): string|nil Read up to `size` bytes from the response body. Returns `nil` when all data has been consumed.
