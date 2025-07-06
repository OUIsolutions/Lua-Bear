

#include "imports/imports.fdefine.h"


int load_lua_bear(lua_State *state){
    LuaCEmbed * l  = newLuaCEmbedLib(state);
    LuaCEmbed_set_string_lib_prop(l, "nil_code","nil");
    LuaCEmbed_add_callback(l, "fetch", private_lua_bear_fetch);
    LuaCEmbed_add_callback(l, "file_stream", private_lua_bear_file_stream);
    return LuaCembed_perform(l);
}

