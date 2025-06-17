
function main()
    darwin.dtw.remove_any("release")

    install_dependencies()


    darwin.silverchain.generate({
        src = "src",
        project_short_cut="luaBear",
        tags = { "dependencie", "consts", "macros", "globals","types", "fdeclare", "fdefine" },
        implement_main = false
    })

  local no_dep_amalgamation = darwin.camalgamator.generate_amalgamation_with_callback("src/one.c",
        function(import, path)
            if import == "src/imports/../dependencie.dependencies.h"  then
                return "dont-include"
            end
            return "include-once"

        end,
        MAX_CONNTENT,
        MAX_RECURSION
    )
    darwin.dtw.write_file("release/luaBear_no_dep.c", no_dep_amalgamation)


    darwin.dtw.copy_any_overwriting("extra/starter.lua","release/luaBear/luaBear.lua")

    local ship = darwin.ship.create_machine("alpine:latest")
    ship.add_comptime_command("apk add gcc musl-dev")
    ship.add_comptime_command("apk add build-base")
    ship.provider = darwin.argv.get_flag_arg_by_index({ "provider"}, 1, "docker")
    ship.start({
        volumes = {
            { ".", "/output" }
        },
        command = "gcc /output/src/one.c  -static -shared -fpic  -o /output/release/luaBear/luaBear.so"
    })

end
