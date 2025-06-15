

#include "imports/imports.fdefine.h"

void start_bear_props(LuaCEmbed *l){

}

int load_lua_bear(lua_State *state){
    LuaCEmbed * l  = newLuaCEmbedLib(state);
    start_bear_props(l);

    return LuaCembed_perform(l);
}
