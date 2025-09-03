#pragma once

#include "engine/resource.h"
#include "engine/resource_manager.h"


namespace physx
{
	class PxConvexMesh;
	class PxMaterial;
	class PxTriangleMesh;
}

namespace Aetherion
{


struct PhysicsSystem;

struct PhysicsMaterialManager : ResourceManager {
	PhysicsMaterialManager(PhysicsSystem& system, IAllocator& allocator);
	~PhysicsMaterialManager();

	Resource* createResource(const Path& path) override;
	void destroyResource(Resource& resource) override;

	IAllocator& allocator;
	PhysicsSystem& system;
};

struct PhysicsMaterial : Resource {
	struct Header {
		static const u32 MAGIC = '_PMA';
		u32 magic = MAGIC;
		u32 version = 0;
	};

	PhysicsMaterial(const Path& path, ResourceManager& resource_manager, struct PhysicsSystem& system, IAllocator& allocator);
	~PhysicsMaterial();

	ResourceType getType() const override { return TYPE; }
	void unload() override;
	bool load(Span<const u8> mem) override;
	//void serialize(OutputMemoryStream& blob);

	PhysicsSystem& system;
	physx::PxMaterial* material;

	static ResourceType TYPE;
};

struct PhysicsGeometry final : Resource
{
	public:
		static const u32 HEADER_MAGIC = 0x5f4c5046; // '_LPF'
		static const ResourceType TYPE;
		struct Header
		{
			u32 m_magic;
			u32 m_version;
			u32 m_convex;
		};

		enum class Versions : u32
		{
			FIRST,
			COOKED,

			LAST
		};

	public:
		PhysicsGeometry(const Path& path, ResourceManager& resource_manager, PhysicsSystem& system, IAllocator& allocator);
		~PhysicsGeometry();

		ResourceType getType() const override { return TYPE; }


	public:
		physx::PxTriangleMesh* tri_mesh;
		physx::PxConvexMesh* convex_mesh;

	private:
		PhysicsSystem& system;

		void unload() override;
		bool load(Span<const u8> mem) override;

};


} // namespace Aetherion