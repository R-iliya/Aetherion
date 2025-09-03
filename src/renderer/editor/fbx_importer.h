#pragma once

namespace Aetherion {

struct ModelImporter;
struct StudioApp;
struct IAllocator;

ModelImporter* createFBXImporter(StudioApp& app, IAllocator& allocator);
void destroyFBXImporter(ModelImporter& importer);

} // namespace Aetherion