//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.fdeclare.h"
//silver_chain_scope_end


LuaCEmbedResponse *private_lua_bear_file_stream(LuaCEmbed *args){
    LuaCEmbedTable *self = LuaCembed_new_anonymous_table(args);
    LuaCEmbedTable_set_bool_prop(self, "lua_bear_is_file_stream", true);
    char *filename = LuaCEmbed_get_str_arg(args,0);
    LuaCEmbedTable_set_string_prop(self, "filename", filename);

    if(LuaCEmbed_has_errors(args)){
        return LuaCEmbed_send_error(LuaCEmbed_get_error_message(args));
    }
    if(LuaCEmbed_get_arg_type(args,1)!= LUA_CEMBED_NIL){
        char *content_type = LuaCEmbed_get_str_arg(args, 1);
        if(LuaCEmbed_has_errors(args)){
            return LuaCEmbed_send_error(LuaCEmbed_get_error_message(args));
        }
        LuaCEmbedTable_set_string_prop(self, "content_type", content_type);
    }
    return LuaCEmbed_send_table(self);
}

LuaCEmbedResponse *private_lua_bear_fetch(LuaCEmbed *args){
    LuaCEmbedTable * entrie_table = LuaCEmbed_get_arg_table(args, 0);
    char *url = LuaCembedTable_get_string_prop(entrie_table, "url");
     if(LuaCEmbed_has_errors(args)){
        return LuaCEmbed_send_error(LuaCEmbed_get_error_message(args));
    }
    BearHttpsRequest *request =newBearHttpsRequest(url);
    
    if(LuaCEmbedTable_get_type_prop(entrie_table, "method") != LUA_CEMBED_NIL){
       char * metod = LuaCembedTable_get_string_prop(entrie_table, "method");
       if(LuaCEmbed_has_errors(args)){
         BearHttpsRequest_free(request);
          return LuaCEmbed_send_error(LuaCEmbed_get_error_message(args));
       }
       BearHttpsRequest_set_method(request, metod);
    }
   
    bool content_type_setted = false;
    int body_type =LuaCEmbedTable_get_type_prop(entrie_table, "body"); 

    if(LuaCEmbedTable_get_type_prop(entrie_table, "headers") != LUA_CEMBED_NIL){
       LuaCEmbedTable * headders_table = LuaCEmbedTable_get_sub_table_by_key(entrie_table, "headers");
       if(LuaCEmbed_has_errors(args)){
         BearHttpsRequest_free(request);
          return LuaCEmbed_send_error(LuaCEmbed_get_error_message(args));
       }
       long headders_size = LuaCEmbedTable_get_full_size(headders_table);
       for(long i = 0; i < headders_size; i++){
           char * key = LuaCembedTable_get_key_by_index(headders_table, i);
            
           if(body_type != LUA_CEMBED_NIL){
                if(strcmp(key, "Content-Type") == 0){
                    content_type_setted = true;
                }
            }


           char * value = LuaCembedTable_get_string_prop(headders_table, key);
           if(LuaCEmbed_has_errors(args)){
             BearHttpsRequest_free(request);
              return LuaCEmbed_send_error(LuaCEmbed_get_error_message(args));
           }
           BearHttpsRequest_add_header(request, key, value);
       }
    }
 
    if(body_type == LUA_CEMBED_STRING){
           lua_Integer body_size;
           unsigned char * body = LuaCembedTable_get_raw_string_prop(entrie_table, "body",&body_size);
           BearHttpsRequest_send_any(request, body, body_size);       
           if(!content_type_setted){
                bool is_binary = false;
                for(int i=0; i < body_size; i++){
                    if(body[i] == 0){
                        is_binary = true;
                        break;
                    }
                }
                if(is_binary){
                    BearHttpsRequest_add_header(request, "Content-Type", "application/octet-stream");
                }
                else{
                    BearHttpsRequest_add_header(request, "Content-Type", "text/plain");
                }
            }
      
    }
    if(body_type == LUA_CEMBED_TABLE){

        LuaCEmbedTable * body_table = LuaCEmbedTable_get_sub_table_by_key(entrie_table, "body");
        //means its a file stream

        bool is_file_stream = LuaCEmbedTable_get_type_prop(body_table, "lua_bear_is_file_stream") == LUA_CEMBED_BOOL;
        if(is_file_stream){
            char *filename = LuaCembedTable_get_string_prop(body_table, "filename");
            bool content_type_provided = LuaCEmbedTable_get_type_prop(body_table, "content_type") == LUA_CEMBED_STRING;
            if(content_type_provided){
                char *content_type = LuaCembedTable_get_string_prop(body_table, "content_type");
                BearHttpsRequest_send_file(request, filename, content_type);
            }
            if(!content_type_provided){
                BearHttpsRequest_send_file_auto_detect_content_type(request, filename);
            }
        }


        if(!is_file_stream){
            char *nil_code = LuaCEmbed_get_string_lib_prop(args, "nil_code");   
            cJSON * body_json = private_lua_bear_json_dump_to_cJSON_object(body_table, nil_code);
            BearHttpsRequest_send_cJSON_with_ownership_control(request, body_json,BEARSSL_HTTPS_GET_OWNERSHIP);
        }


    }
        
        
    if(body_type != LUA_CEMBED_NIL && body_type != LUA_CEMBED_STRING && body_type != LUA_CEMBED_TABLE){
            BearHttpsRequest_free(request);
            return LuaCEmbed_send_error("body must me a table or a string" );
    }



    if(LuaCEmbed_has_errors(args)){
        return LuaCEmbed_send_error(LuaCEmbed_get_error_message(args));
    }
    BearHttpsResponse *response = BearHttpsRequest_fetch(request);
    BearHttpsRequest_free(request);

    return private_lua_bear_create_response_obj(args,response);

}