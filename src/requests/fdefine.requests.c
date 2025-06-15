//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.fdeclare.h"
//silver_chain_scope_end




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
        char *nil_code = LuaCEmbed_get_string_lib_prop(args, "nil_code");
        cJSON * body_json = private_lua_bear_json_dump_to_cJSON_object(entrie_table, nil_code);
        BearHttpsRequest_send_cJSON_with_ownership_control(request, body_json,BEARSSL_HTTPS_GET_OWNERSHIP);
        if(!content_type_setted){
            BearHttpsRequest_add_header(request, "Content-Type", "application/json");
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