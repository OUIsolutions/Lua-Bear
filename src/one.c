

#include "imports/imports.fdefine.h"


int load_lua_bear(lua_State *state){
    LuaCEmbed * l  = newLuaCEmbedLib(state);
    LuaCEmbed_set_string_lib_prop(l, "nil_code","nil");
    LuaCEmbed_add_callback(l, "fetch", private_lua_bear_fetch);
    return LuaCembed_perform(l);
}
