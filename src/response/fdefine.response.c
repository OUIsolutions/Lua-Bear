//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.fdeclare.h"
//silver_chain_scope_end

LuaCEmbedResponse * private_lua_bear_read_body(LuaCEmbedTable *self,LuaCEmbed *args) {
    BearHttpsResponse *response = (BearHttpsResponse *)(bear_ptr_cast)LuaCembedTable_get_long_prop(self, "bear_response_ojb");
    unsigned char *body = BearHttpsResponse_read_body(response);
    if(BearHttpsResponse_error(response)){
         char *error_msg = BearHttpsResponse_get_error_msg(response);
         return LuaCEmbed_send_error(error_msg);
    }
    return LuaCEmbed_send_raw_string(body, response->body_size);
}

LuaCEmbedResponse * private_lua_bear_read_body_json(LuaCEmbedTable *self,LuaCEmbed *args) {
    BearHttpsResponse *response = (BearHttpsResponse *)(bear_ptr_cast)LuaCembedTable_get_long_prop(self, "bear_response_ojb");
   const  char *body = BearHttpsResponse_read_body_str(response);
    if(BearHttpsResponse_error(response)){
         char *error_msg = BearHttpsResponse_get_error_msg(response);
         return LuaCEmbed_send_error(error_msg);
    }
    char *nil_code = LuaCEmbed_get_string_lib_prop(args, "nil_code");
    return private_lua_bear_loads_json_from_raw_string(args, body, nil_code);
}


LuaCEmbedResponse * private_lua_bear_read_body_chunck(LuaCEmbedTable *self,LuaCEmbed *args) {
    BearHttpsResponse *response = (BearHttpsResponse *)(bear_ptr_cast)LuaCembedTable_get_long_prop(self, "bear_response_ojb");
    
    long chunk_size = LuaCEmbed_get_long_arg(args, 0);
    if(LuaCEmbed_has_errors(args)){
        return LuaCEmbed_send_error(LuaCEmbed_get_error_message(args));
    }
    unsigned char *chunk = malloc(chunk_size + 1);
    BearHttpsResponse_read_body_chunck(response,chunk, chunk_size);
    if(BearHttpsResponse_error(response)){
         free(chunk);
         char *error_msg = BearHttpsResponse_get_error_msg(response);
         return LuaCEmbed_send_error(error_msg);
    }
    chunk[chunk_size] = '\0'; // Ensure null-termination
    LuaCEmbedResponse *lua_response = LuaCEmbed_send_raw_string(chunk, chunk_size);
    free(chunk);
    return lua_response;
}




LuaCEmbedResponse * private_lua_bear_create_response_obj(LuaCEmbed *args,BearHttpsResponse *response) {
  
    if(BearHttpsResponse_error(response)){
        char *error_msg  =  BearHttpsResponse_get_error_msg(response);
        LuaCEmbedResponse *error_response = LuaCEmbed_send_error(error_msg);
        BearHttpsResponse_free(response);
        return error_response;
    }
    LuaCEmbedTable *self = LuaCembed_new_anonymous_table(args);
    LuaCEmbedTable_set_method(self, "read_body", private_lua_bear_read_body);
    LuaCEmbedTable_set_method(self, "read_body_json", private_lua_bear_read_body_json);
    LuaCEmbedTable_set_method(self, "read_body_chunck", private_lua_bear_read_body_chunck);
    LuaCEmbedTable_set_long_prop(self,"bear_response_ojb",(bear_ptr_cast)response);
    LuaCEmbedTable_set_long_prop(self,"status_code", response->status_code);
    LuaCEmbedTable *headders = LuaCembed_new_anonymous_table(args);
    LuaCEmbedTable_set_sub_table_prop(self, "headers", headders);
    int headders_size = BearHttpsResponse_get_headers_size(response);
    for (int i = 0; i < headders_size; i++) {
        char *key = BearHttpsResponse_get_header_key_by_index(response, i);
        char *value = BearHttpsResponse_get_header_value_by_index(response, i);
        LuaCEmbedTable_set_string_prop(self, key, value);
    }
    return LuaCEmbed_send_table(self);

}