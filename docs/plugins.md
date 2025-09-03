# How to download plugins
1. Execute [scripts/plugins.bat](../scripts/plugins.bat).
2. Select the desired plugin.
3. Regenerate the solution (e.g., run [scripts/create_vs22_sln.bat](../scripts/create_vs22_sln.bat)).
4. Build and run the solution.

Plugins downloaded this way are placed in the `plugins` directory. *GENie* automatically detects all plugins in this directory and includes them in the solution.

# Up to date plugins

Note: plugins in this section are compilable/runnable, but some of them are only in prototype stage 

* [Node-based shader editor](https://github.com/nem0/aetherionengine_shader_editor)
* [Real-world terrains, roads and buildings](https://github.com/nem0/aetherionEngine_maps)
* [Rml UI](https://github.com/nem0/aetherionengine_rml)
* [Visual scripting](https://github.com/nem0/aetherionengine_visualscript)
* [JavaScript](https://github.com/nem0/aetherionEngine_js)
* [Procedural geometry](https://github.com/nem0/aetherionengine_procedural_geom)
* [Network](https://github.com/nem0/aetherionengine_net)
* [Marketplace](https://github.com/nem0/aetherionengine_market)
* [C#](https://github.com/nem0/aetherionengine_csharp)
* [LiveCode](https://github.com/nem0/aetherionengine_livecode)
* [GLTF importer](https://github.com/nem0/aetherionengine_gltf)

# Deprecated

Note: not supported, most likely won't build with latest engine, but can be resurrected 

* [DX11 & DX12](https://github.com/nem0/aetherionengine_dx11) - DX12 is now integrated in Engine, old APIs (DX11) are not supported.
* [FBX importer using Autodesk's SDK](https://github.com/nem0/aetherionEngine_fbx)
* [HTML/CSS rendering](https://github.com/nem0/aetherionengine_html)
* [Turbo Badger](https://github.com/nem0/aetherionengine_turbobadger)

