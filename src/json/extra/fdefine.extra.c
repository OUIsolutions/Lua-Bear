//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end

bool private_lua_bear_table_is_object(LuaCEmbedTable *table){
    long size = LuaCEmbedTable_get_full_size(table);
    for(int i =0; i < size;i++){
        if(LuaCembedTable_has_key_at_index(table,i) == false){
            return false;
        }
    }
    return true;
}