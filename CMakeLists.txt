# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Tutorials)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# engine
add_executable(engine

	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	engine/Buffers/FBO/FBO.h
	engine/Buffers/FBO/FBO.cpp
	engine/Buffers/VAO/VAO.h
	engine/Buffers/VAO/VAO.cpp
	engine/Buffers/VBO/VBO.h
	engine/Buffers/VBO/VBO.cpp
	
	engine/Camera/Camera/Camera.h
	engine/Camera/Camera/Camera.cpp
	engine/Camera/EditorCamera/EditorCamera.h
	engine/Camera/EditorCamera/EditorCamera.cpp
	engine/Camera/OrbitalCamera/OrbitalCamera.h
	engine/Camera/OrbitalCamera/OrbitalCamera.cpp
	
	engine/Components/Component/Component.h
	engine/Components/Component/Component.cpp
	engine/Components/MeshComponent/MeshComponent.h
	engine/Components/MeshComponent/MeshComponent.cpp
	
	engine/Engine/Engine.h
	engine/Engine/Engine.cpp
	
	engine/FilesPath/FilesPath.h
	
	engine/Inputs/InputManager/InputManager.h
	engine/Inputs/InputManager/InputManager.cpp
	engine/Inputs/MouseManager/MouseManager.h
	engine/Inputs/MouseManager/MouseManager.cpp
	engine/Inputs/Tokens/InputCoreTokens.h
	engine/Inputs/Type/ACTION_TYPE.h
	engine/Inputs/Type/Axis.h
	engine/Inputs/Type/Key.h
	
	engine/Landscape/Landscape/Landscape.h
	engine/Landscape/Landscape/Landscape.cpp
	engine/Landscape/Material/LandscapeMaterial.h
	engine/Landscape/Material/LandscapeMaterial.cpp
	engine/Landscape/Mesh/LandscapeMesh.h
	engine/Landscape/Mesh/LandscapeMesh.cpp
	engine/Landscape/Shader/Landscape_frag.glsl
	engine/Landscape/Shader/Landscape_vertex.glsl
	engine/Landscape/ShaderHandler/LandscapeShaderHandler.h
	engine/Landscape/ShaderHandler/LandscapeShaderHandler.cpp
	
	engine/Lights/PointLight/PointLight.h
	engine/Lights/PointLight/PointLight.cpp
	engine/Lights/DirectionalLight/DirectionalLight.h
	engine/Lights/DirectionalLight/DirectionalLight.cpp
	engine/Lights/LightManager/LightManager.h
	engine/Lights/LightManager/LightManager.cpp
	
	engine/Materials/BaseMaterial/BaseMaterial.h
	engine/Materials/BaseMaterial/BaseMaterial.cpp
	engine/Materials/Material.h
	engine/Materials/Material.cpp
	
	engine/Meshs/Mesh/Mesh.h
	engine/Meshs/Mesh/Mesh.cpp
	engine/Meshs/Cube/Cube.h
	engine/Meshs/Cube/Cube.cpp
	engine/Meshs/Plane/Plane.h
	engine/Meshs/Plane/Plane.cpp
	engine/Meshs/Sphere/Sphere.h
	engine/Meshs/Sphere/Sphere.cpp
	
	engine/Objects/Object/Object.h
	engine/Objects/GameObject/GameObject.h
	engine/Objects/GameObject/GameObject.cpp
	engine/Objects/ObjectManager/ObjectManager.h
	engine/Objects/ObjectManager/ObjectManager.cpp
	
	engine/Physic/Collider/Collider.h
	engine/Physic/Collider/Collider.cpp
	engine/Physic/BoxCollider/BoxCollider.h
	engine/Physic/BoxCollider/BoxCollider.cpp
	engine/Physic/SphereCollider/SphereCollider.h
	engine/Physic/SphereCollider/SphereCollider.cpp
	engine/Physic/CollisionData/CollisionData.h
	engine/Physic/CollisionData/CollisionData.cpp
	engine/Physic/PhysicComponent/PhysicComponent.h
	engine/Physic/PhysicComponent/PhysicComponent.cpp
	engine/Physic/PhysicManager/PhysicManager.h
	engine/Physic/PhysicManager/PhysicManager.cpp
	
	engine/Planets/Planet/Planet.h
	engine/Planets/Planet/Planet.cpp
	
	engine/Renderer/Renderer.h
	engine/Renderer/Renderer.cpp
	
	engine/Scenes/Scene/Scene.h
	engine/Scenes/Scene/Scene.cpp
	engine/Scenes/SceneManager/SceneManager.h
	engine/Scenes/SceneManager/SceneManager.cpp

	engine/Game/Scenes/SceneMain.h
	engine/Game/Scenes/SceneMain.cpp
	engine/Game/Asteroid/Asteroid.h
	engine/Game/Asteroid/Asteroid.cpp
	engine/Game/Scenes/Scene_Earth.h
	engine/Game/Scenes/Scene_Earth.cpp
	engine/Game/Scenes/Scene_Moon.h
	engine/Game/Scenes/Scene_Moon.cpp
	engine/Game/Scenes/Scene_Mars.h
	engine/Game/Scenes/Scene_Mars.cpp
	engine/Game/Player/Player.h
	engine/Game/Player/Player.cpp
	engine/Game/Player/Ground_Player.h
	engine/Game/Player/Ground_Player.cpp
	engine/Game/Decor/Spaceship.h
	engine/Game/Decor/Spaceship.cpp
	engine/Game/Manager/GameManager.h
	engine/Game/Manager/GameManager.cpp
	engine/Game/Weapon/Projectile.h
	engine/Game/Weapon/Projectile.cpp
	engine/Game/Collectibles/Trophy.h
	engine/Game/Collectibles/Trophy.cpp
	
	engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h
	engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.cpp
	engine/ShaderHandlers/ShaderHandler/ShaderHandler.h
	engine/ShaderHandlers/ShaderHandler/ShaderHandler.cpp
	engine/ShaderHandlers/ShaderManager/ShaderManager.h
	engine/ShaderHandlers/ShaderManager/ShaderManager.cpp
	
	engine/Skyboxes/Skybox/Skybox.h
	engine/Skyboxes/Skybox/Skybox.cpp
	engine/Skyboxes/Material/SkyboxMaterial.h
	engine/Skyboxes/Material/SkyboxMaterial.cpp
	engine/Skyboxes/Mesh/SkyboxMesh.h
	engine/Skyboxes/Mesh/SkyboxMesh.cpp
	engine/Skyboxes/Shader/Skybox_frag.glsl
	engine/Skyboxes/Shader/Skybox_vertex.glsl
	engine/Skyboxes/ShaderHandler/SkyboxShaderHandler.h
	engine/Skyboxes/ShaderHandler/SkyboxShaderHandler.cpp
	
	engine/Transform/Transform.h
	engine/Transform/Transform.cpp
	engine/Transform/Material/TransformMaterial.h
	engine/Transform/Material/TransformMaterial.cpp
	engine/Transform/Mesh/TransformMesh.h
	engine/Transform/Mesh/TransformMesh.cpp
	engine/Transform/Shader/Transform_frag.glsl
	engine/Transform/Shader/Transform_vertex.glsl
	
	engine/Utils/Printer/Printer.h
	engine/Utils/Singleton/Singleton.h
	engine/Utils/AssimpLoader/AssimpLoader.h
	engine/Utils/AssimpLoader/AssimpLoader.cpp
	engine/Utils/TextureLoader/TextureLoader.h
	engine/Utils/TextureLoader/TextureLoader.cpp
	engine/Utils/Interfaces/IMoving.h
	engine/Utils/Interfaces/IRotating.h
	engine/Utils/Interfaces/ITickable.h
	engine/Utils/Interfaces/IRenderable.h
	
	engine/Windows/Window.h
	engine/Windows/Window.cpp
	
	engine/main.cpp
)
target_link_libraries(engine
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(engine PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/engine/")
create_target_launcher(engine WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/engine/")




SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET engine POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/engine${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/engine/"
)
elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

