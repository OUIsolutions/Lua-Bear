function install_dependencies()
    local hasher = darwin.dtw.newHasher()
    hasher.digest_folder_by_content("dependencies")
    local EXPECTED_SHA = '3f16fdc8841db38b030b059a83ed3f0e1746ee3f115ff1c8265007b9f372728d'
    if hasher.get_value() == EXPECTED_SHA then
        return
    end
    
    darwin.dtw.remove_any("dependencies")
    os.execute("mkdir -p dependencies")

    
    os.execute("curl -L https://github.com/OUIsolutions/LuaCEmbed/releases/download/0.8.3/LuaCEmbedOne.c -o dependencies/LuaCEmbedOne.c")
    os.execute("curl -L https://github.com/OUIsolutions/BearHttpsClient/releases/download/0.3.0/BearHttpsClientOne.c -o dependencies/BearHttpsClientOne.c")


    local new_hasher = darwin.dtw.newHasher()
    new_hasher.digest_folder_by_content("dependencies")
    print("new hasher is: " .. new_hasher.get_value())
end