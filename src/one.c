

#include "imports/imports.fdefine.h"

void start_bear_props(LuaCEmbed *l){
    LuaCEmbed_set_string_lib_prop(l, "nil_code","nil");
    LuaCEmbed_add_callback(l, "fetch", private_lua_bear_fetch);
}

int load_lua_bear(lua_State *state){
    LuaCEmbed * l  = newLuaCEmbedLib(state);
    start_bear_props(l);

    return LuaCembed_perform(l);
}
