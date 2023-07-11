#pragma once

#ifdef _MSC_VER
// HACK(mihe): CMake's Visual Studio generator doesn't support system include paths
#pragma warning(push, 0)

// Pushing level 0 doesn't seem to disable the ones we've explicitly enabled
// C4245: conversion from 'type1' to 'type2', signed/unsigned mismatch
// C4365: conversion from 'type1' to 'type2', signed/unsigned mismatch
#pragma warning(disable : 4245 4365)
#endif // _MSC_VER

#include <core/typedefs.h>
#include <core/config/engine.h>
#include <core/config/project_settings.h>
#include <core/error/error_macros.h>
#include <core/math/math_defs.h>
#include <core/object/class_db.h>
#include <core/object/object.h>
#include <core/object/worker_thread_pool.h>
#include <core/os/memory.h>
#include <core/os/os.h>
#include <core/templates/hashfuncs.h>
#include <core/variant/variant.h>
#include <core/variant/variant_utility.cpp>

#include <scene/3d/camera_3d.h>
#include <scene/3d/visual_instance_3d.h>
#include <scene/main/viewport.h>
#include <scene/resources/material.h>
#include <scene/resources/mesh.h>
#include <scene/resources/world_3d.h>

#include <servers/physics_server_3d.h>
#include <servers/rendering_server.h>
#include <servers/extensions/physics_server_3d_extension.h>

#include <Jolt/Jolt.h>

#include <Jolt/Core/Factory.h>
#include <Jolt/Core/FixedSizeFreeList.h>
#include <Jolt/Core/IssueReporting.h>
#include <Jolt/Core/JobSystemWithBarrier.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Geometry/ConvexSupport.h>
#include <Jolt/Geometry/GJKClosestPoint.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseQuery.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/CollidePointResult.h>
#include <Jolt/Physics/Collision/CollideShape.h>
#include <Jolt/Physics/Collision/CollisionDispatch.h>
#include <Jolt/Physics/Collision/CollisionGroup.h>
#include <Jolt/Physics/Collision/ContactListener.h>
#include <Jolt/Physics/Collision/EstimateCollisionResponse.h>
#include <Jolt/Physics/Collision/GroupFilter.h>
#include <Jolt/Physics/Collision/NarrowPhaseQuery.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/ConvexHullShape.h>
#include <Jolt/Physics/Collision/Shape/CylinderShape.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Collision/Shape/ScaledShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/StaticCompoundShape.h>
#include <Jolt/Physics/Constraints/FixedConstraint.h>
#include <Jolt/Physics/Constraints/HingeConstraint.h>
#include <Jolt/Physics/Constraints/PointConstraint.h>
#include <Jolt/Physics/Constraints/SixDOFConstraint.h>
#include <Jolt/Physics/Constraints/SliderConstraint.h>
#include <Jolt/Physics/Constraints/SwingTwistConstraint.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

#ifdef JPH_DEBUG_RENDERER
#include <Jolt/Renderer/DebugRenderer.h>
#endif // JPH_DEBUG_RENDERER

#include <mimalloc.h>

#include <algorithm>
#include <atomic>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

using namespace godot;

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#include "containers/free_list.hpp"
#include "containers/hash_map.hpp"
#include "containers/hash_set.hpp"
#include "containers/inline_vector.hpp"
#include "containers/local_vector.hpp"
#include "containers/rid_owner.hpp"
#include "misc/bind_macros.hpp"
#include "misc/error_macros.hpp"
#include "misc/gdclass_macros.hpp"
#include "misc/math.hpp"
#include "misc/scope_guard.hpp"
#include "misc/type_conversions.hpp"
#include "misc/utility_functions.hpp"
