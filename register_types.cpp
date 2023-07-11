#include "register_types.h"

#include "objects/jolt_physics_direct_body_state_3d.hpp"
#include "servers/jolt_globals.hpp"
#include "servers/jolt_physics_server_3d.hpp"
#include "servers/jolt_physics_server_factory_3d.hpp"
#include "servers/jolt_project_settings.hpp"
#include "spaces/jolt_debug_geometry_3d.hpp"
#include "spaces/jolt_physics_direct_space_state_3d.hpp"

#include <mimalloc-new-delete.h>

#include "jolt.h"

JoltPhysicsServerFactory3D* server_factory = nullptr;

void initialize_jolt_module(ModuleInitializationLevel p_level) {
	switch (p_level) {
		case MODULE_INITIALIZATION_LEVEL_CORE: {
		} break;
		case MODULE_INITIALIZATION_LEVEL_SERVERS: {
			jolt_initialize();

			ClassDB::register_class<JoltPhysicsDirectBodyState3D>();
			ClassDB::register_class<JoltPhysicsDirectSpaceState3D>();
			ClassDB::register_class<JoltPhysicsServer3D>();
			ClassDB::register_class<JoltPhysicsServerFactory3D>();

			server_factory = memnew(JoltPhysicsServerFactory3D);

			PhysicsServer3DManager::get_singleton()->register_server(
				"JoltPhysics3D",
				Callable(server_factory, "create_server")
			);
		} break;
		case MODULE_INITIALIZATION_LEVEL_SCENE: {
			JoltProjectSettings::register_settings();

			ClassDB::register_class<JoltDebugGeometry3D>();
		} break;
		case MODULE_INITIALIZATION_LEVEL_EDITOR: {
		} break;
	}
}

void uninitialize_jolt_module(ModuleInitializationLevel p_level) {
	switch (p_level) {
		case MODULE_INITIALIZATION_LEVEL_CORE: {
		} break;
		case MODULE_INITIALIZATION_LEVEL_SERVERS: {
			memdelete_safely(server_factory);

			jolt_deinitialize();
		} break;
		case MODULE_INITIALIZATION_LEVEL_SCENE: {
		} break;
		case MODULE_INITIALIZATION_LEVEL_EDITOR: {
		} break;
	}
}