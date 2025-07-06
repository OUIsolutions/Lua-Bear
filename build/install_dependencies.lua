function install_dependencies()
    local hasher = darwin.dtw.newHasher()
    hasher.digest_folder_by_content("dependencies")
    local EXPECTED_SHA = '7095279fe66dd6df7a415b31467047fe88abc54d2ee06a78c3997968972afc50'
    if hasher.get_value() == EXPECTED_SHA then
        return
    end
    
    darwin.dtw.remove_any("dependencies")
    os.execute("mkdir -p dependencies")

    
    os.execute("curl -L https://github.com/OUIsolutions/LuaCEmbed/releases/download/v0.780/LuaCEmbed.h -o dependencies/LuaCEmbed.h")
    os.execute("curl -L https://github.com/OUIsolutions/BearHttpsClient/releases/download/0.3.0/BearHttpsClientOne.c -o dependencies/BearHttpsClientOne.c")


    local new_hasher = darwin.dtw.newHasher()
    new_hasher.digest_folder_by_content("dependencies")
    print("new hasher is: " .. new_hasher.get_value())
end