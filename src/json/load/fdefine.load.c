//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end


LuaCEmbedTable * private_lua_bear_parse_array(LuaCEmbed *args, cJSON *json_array,const char *nil_code){
    LuaCEmbedTable *created = LuaCembed_new_anonymous_table(args);
    int size = cJSON_GetArraySize(json_array);
    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(json_array,i);
        if(cJSON_IsNumber(current)){
            LuaCEmbedTable_append_double(created,cJSON_GetNumberValue(current));
        }
        else if(cJSON_IsString(current)){
            LuaCEmbedTable_append_string(created,cJSON_GetStringValue(current));
        }
        else if(cJSON_IsBool(current)){
            LuaCEmbedTable_append_bool(created,(bool)current->valueint);
        }
        else if(cJSON_IsNull(current)){
            LuaCEmbedTable_append_string(created, nil_code);
        }
        else if(cJSON_IsObject(current)){
            LuaCEmbedTable *internal_created = private_lua_bear_parse_object(args,current);
            LuaCEmbedTable_append_table(created,internal_created);
        }
        else if(cJSON_IsArray(current)){
            LuaCEmbedTable *internal_created = private_lua_bear_parse_array(args,current);
            LuaCEmbedTable_append_table(created,internal_created);
        }
    }
    return created;

}

LuaCEmbedTable * private_lua_bear_parse_object(LuaCEmbed *args, cJSON *json_object,const char *nil_code){
    LuaCEmbedTable *created = LuaCembed_new_anonymous_table(args);
    int size = cJSON_GetArraySize(json_object);
    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(json_object,i);
        char *key =current->string;
        if(cJSON_IsNumber(current)){
            LuaCEmbedTable_set_double_prop(created,key, cJSON_GetNumberValue(current));
        }
        else if(cJSON_IsString(current)){
            LuaCEmbedTable_set_string_prop(created,key, cJSON_GetStringValue(current));
        }
        else if(cJSON_IsBool(current)){
            LuaCEmbedTable_set_bool_prop(created,key, (bool)current->valueint);
        }
        else if(cJSON_IsNull(current)){
            LuaCEmbedTable_set_string_prop(created, key, nil_code);
        }
        else if(cJSON_IsObject(current)){
            LuaCEmbedTable *internal_created = private_lua_bear_parse_object(args,current);
            LuaCEmbedTable_set_sub_table_prop(created,key,internal_created);
        }
        else if(cJSON_IsArray(current)){
            LuaCEmbedTable *internal_created = private_lua_bear_parse_array(args,current);
            LuaCEmbedTable_set_sub_table_prop(created,key,internal_created);
        }
    }
    return created;

}

LuaCEmbedResponse * private_lua_bear_loads_json_from_raw_string(LuaCEmbed *args,const char * str,const char *nil_code){
    cJSON *parsed = cJSON_Parse(str);
    if(!parsed){
        return LuaCEmbed_send_error("not a valid json");
    }

    //here means its parsed correct
    if(cJSON_IsBool(parsed)){
        LuaCEmbedResponse *response =LuaCEmbed_send_bool((bool)parsed->valueint);
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsNumber(parsed)){
        LuaCEmbedResponse *response =LuaCEmbed_send_double(cJSON_GetNumberValue(parsed));
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsString(parsed)){
        LuaCEmbedResponse *response =LuaCEmbed_send_str(cJSON_GetStringValue(parsed));
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsNull(parsed)){
        cJSON_Delete(parsed);
        return  LuaCEmbed_send_str(nil_code);
    }
    else if(cJSON_IsObject(parsed)){
        LuaCEmbedTable *created = private_lua_bear_parse_object(args,parsed,nil_code);
        cJSON_Delete(parsed);
        return LuaCEmbed_send_table(created);
    }
    else if(cJSON_IsArray(parsed)){
        LuaCEmbedTable *created = private_lua_bear_parse_array(args,parsed,nil_code);
        cJSON_Delete(parsed);
        return LuaCEmbed_send_table(created);
    }

    return NULL;
}
