//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end

cJSON  * private_lua_bear_json_dump_to_cJSON_array(LuaCEmbedTable *table,const char *nil_code){
    long size = LuaCEmbedTable_get_full_size(table);
    cJSON * created_array = cJSON_CreateArray();
    for(int i = 0; i<size;i++){
        int type = LuaCEmbedTable_get_type_by_index(table,i);

        if(type == LUA_CEMBED_NUMBER){
            double value = LuaCEmbedTable_get_double_by_index(table,i);
            cJSON_AddItemToArray(created_array, cJSON_CreateNumber(value));
        }

        if(type == LUA_CEMBED_STRING){
            char *value = LuaCEmbedTable_get_string_by_index(table,i);

            if(strcmp(nil_code, value) == 0){
                cJSON_AddItemToArray(created_array, cJSON_CreateNull());

            }else{
                cJSON_AddItemToArray(created_array, cJSON_CreateString(value));

            }
        }

        if(type == LUA_CEMBED_BOOL){
            bool value = LuaCEmbedTable_get_bool_by_index(table,i);
            cJSON_AddItemToArray(created_array, cJSON_CreateBool(value));
        }

        if(type == LUA_CEMBED_TABLE){
            LuaCEmbedTable *internal = LuaCEmbedTable_get_sub_table_by_index(table,i);
            cJSON *value = private_lua_bear_json_dump_table_to_cJSON(internal);
            cJSON_AddItemToArray(created_array, value);
        }

    }
    return created_array;
}


// Função de comparação para qsort
static int private_lua_bear_compare_keys(const void *a, const void *b) {
    return strcmp(((private_lua_bear_KeyIndexPair*)a)->key, ((private_lua_bear_KeyIndexPair*)b)->key);
}

cJSON  * private_lua_bear_json_dump_to_cJSON_object(LuaCEmbedTable *table, const char *nil_code){
    long size = LuaCEmbedTable_get_full_size(table);
    cJSON * created_object = cJSON_CreateObject();
    
    // Criar array para armazenar pares de chave-índice
    private_lua_bear_KeyIndexPair *pairs = (private_lua_bear_KeyIndexPair*)malloc(size * sizeof(private_lua_bear_KeyIndexPair));
    if (!pairs) {
        // Em caso de falha na alocação, recorrer ao método original
        for(int i = 0; i < size; i++){
            char *key = LuaCembedTable_get_key_by_index(table, i);
            int type = LuaCEmbedTable_get_type_by_index(table, i);
            
            if(type == LUA_CEMBED_NUMBER){
                double value = LuaCEmbedTable_get_double_by_index(table,i);
                cJSON_AddNumberToObject(created_object,key,value);
            }
            if(type == LUA_CEMBED_STRING){
                char *value = LuaCEmbedTable_get_string_by_index(table,i);
                if(strcmp(nil_code,value)==0){
                    cJSON_AddNullToObject(created_object,key);
                }else{
                    cJSON_AddStringToObject(created_object,key, value);
                }
            }
            if(type == LUA_CEMBED_BOOL){
                bool value = LuaCEmbedTable_get_bool_by_index(table,i);
                cJSON_AddBoolToObject(created_object,key, value);
            }

            if(type == LUA_CEMBED_TABLE){
                LuaCEmbedTable *internal = LuaCEmbedTable_get_sub_table_by_index(table,i);
                cJSON *value = private_lua_bear_json_dump_table_to_cJSON(internal);
                cJSON_AddItemToObject(created_object,key,value);
            }
        }
        return created_object;
    }
    
    // Preencher o array com as chaves e seus índices
    for(int i = 0; i < size; i++){
        pairs[i].key = LuaCembedTable_get_key_by_index(table, i);
        pairs[i].index = i;
    }
    
    // Ordenar as chaves alfabeticamente
    qsort(pairs, size, sizeof(private_lua_bear_KeyIndexPair), private_lua_bear_compare_keys);
    
    // Adicionar os elementos ao objeto JSON na ordem ordenada
    for(int i = 0; i < size; i++){
        char *key = pairs[i].key;
        int idx = pairs[i].index;
        int type = LuaCEmbedTable_get_type_by_index(table, idx);
        
        if(type == LUA_CEMBED_NUMBER){
            double value = LuaCEmbedTable_get_double_by_index(table, idx);
            cJSON_AddNumberToObject(created_object, key, value);
        }
        if(type == LUA_CEMBED_STRING){
            char *value = LuaCEmbedTable_get_string_by_index(table, idx);
            if(strcmp(nil_code, value) == 0){
                cJSON_AddNullToObject(created_object, key);
            }else{
                cJSON_AddStringToObject(created_object, key, value);
            }
        }
        if(type == LUA_CEMBED_BOOL){
            bool value = LuaCEmbedTable_get_bool_by_index(table, idx);
            cJSON_AddBoolToObject(created_object, key, value);
        }
        if(type == LUA_CEMBED_TABLE){
            LuaCEmbedTable *internal = LuaCEmbedTable_get_sub_table_by_index(table, idx);
            cJSON *value = private_lua_bear_json_dump_table_to_cJSON(internal);
            cJSON_AddItemToObject(created_object, key, value);
        }
    }
    
    // Liberar memória
    free(pairs);
    
    return created_object;
}

cJSON  * private_lua_bear_json_dump_table_to_cJSON(LuaCEmbedTable *table, const char *nil_code){

    if(lua_json_fluid_table_is_object(table)){

        return private_lua_bear_json_dump_to_cJSON_object(table, nil_code);
    }
    return private_lua_bear_json_dump_to_cJSON_array(table, nil_code);
}



