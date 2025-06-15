
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
    os.execute("gcc src/one.c  -shared  -fpic -o release/luaBear/luaBear.so")

    --zip the folder 
    os.execute("cd release && zip -r luaBear.zip luaBear")
end