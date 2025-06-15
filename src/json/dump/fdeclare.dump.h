//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.types.h"
//silver_chain_scope_end



cJSON  * private_lua_bear_json_dump_to_cJSON_array(LuaCEmbedTable *table,const char *nil_code);

// Função de comparação para qsort
static int private_lua_bear_compare_keys(const void *a, const void *b);

cJSON  * private_lua_bear_json_dump_to_cJSON_object(LuaCEmbedTable *table, const char *nil_code);

cJSON  * private_lua_bear_json_dump_table_to_cJSON(LuaCEmbedTable *table, const char *nil_code);