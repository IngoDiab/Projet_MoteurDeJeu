#include "Scene_Mars.h"
#include "engine/FilesPath/FilesPath.h"
#include "engine/Game/Decor/Spaceship.h"
#include "engine/Game/Player/Ground_Player.h"
#include "engine/Landscape/Landscape/Landscape.h"
#include "engine/Landscape/Material/LandscapeMaterial.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Inputs/InputManager/InputManager.h"
#include "engine/Camera/EditorCamera/EditorCamera.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"
#include "engine/Engine/Engine.h"

#include "engine/Game/Collectibles/Trophy.h"
#include "engine/Lights/LightManager/LightManager.h"

void Scene_Mars::LoadScene()
{
    Skybox* _skybox = Skybox::Instance();
    _skybox->ChangeSkybox("Textures/Skybox/Mars/", ".png");

    mCharacter = CreateCharacter();
    mSpaceship = CreateSpaceship();
    mLandscape = CreateLandscape();

    InitEditorCamera();
    BindCharacterInput();

    mCharacter->ClipToLandscape(mLandscape);
    mSpaceship->ClipToLandscape(mLandscape);

    ObjectManager* _objectManager = ObjectManager::Instance();

    DirectionalLight* _sunLight = _objectManager->Create<DirectionalLight>();
    _sunLight->SetColor(vec3(1));
    _sunLight->SetDirection(vec3(-1,-1,1));

    CreateTrophy();
}

Ground_Player* Scene_Mars::CreateCharacter()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Ground_Player* _character = _objectManager->Create<Ground_Player>();
    _character->SetPosition(vec3(-118.553f,-140.0f,-2994.34f));

    MeshComponent* _meshComponent = _character->GetComponent<MeshComponent>();

    return _character;
}

Spaceship* Scene_Mars::CreateSpaceship()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Spaceship* _spaceship = _objectManager->Create<Spaceship>(vec3(-218.553f,-140.0f,-2994.34f), vec3(0), vec3(1));
    return _spaceship;
}

Trophy* Scene_Mars::CreateTrophy()
{
    if(!mCollectibleAvailable) return nullptr;
    ObjectManager* _objectManager = ObjectManager::Instance();
    Trophy* _trophy = _objectManager->Create<Trophy>(vec3(4685.42f, -97.0441f, 4492.02f));
    _trophy->GetCollider()->SetOnTriggerEnterCallback([=](CollisionData _data) 
    {
        mCollectibleAvailable = false;
        _objectManager->Destroy(_trophy); 
    });

    return _trophy;
}

Landscape* Scene_Mars::CreateLandscape()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Landscape* _landscape = _objectManager->Create<Landscape>(vec3(0,-50,0), vec3(0), vec3(10000,1,10000));
    _landscape->ChangeResolution(256,256);
    _landscape->ApplyHeightmap("Textures/Heightmaps/MarsHeightmap.png",1000000, 100);

    LandscapeMaterial* _landscapeMaterial= _landscape->GetMaterial();
    _landscapeMaterial->AddLayer(0, MARS_GROUND_TEXTURE0);
    _landscapeMaterial->AddLayer(1, MARS_GROUND_TEXTURE1);
    _landscapeMaterial->AddLayer(2, MARS_GROUND_TEXTURE1);
    _landscapeMaterial->SetTiling(200);

    return _landscape;
}

void Scene_Mars::InitEditorCamera() const
{
   EditorCamera::Instance()->SetPosition(vec3(0,10,-50));
}

void Scene_Mars::BindCharacterInput()
{
    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindAxis({{GLFW_KEY_W,GLFW_KEY_S}}, mCharacter, (void* (Object::*)(float))&Ground_Player::MoveForwardBackward);
    _inputManager->BindAxis({{GLFW_KEY_D,GLFW_KEY_A}}, mCharacter, (void* (Object::*)(float))&Ground_Player::MoveLateral);
    _inputManager->BindKey(GLFW_KEY_SPACE, ACTION_TYPE::PRESS, mCharacter, (void* (Object::*)(bool))&Ground_Player::Jump);

    InputManager::Instance()->BindAxis({{MOUSE_Y, MOUSE_Y}}, mCharacter, (void* (Object::*)(float))&Ground_Player::RotateLocalAxisX);
    InputManager::Instance()->BindAxis({{MOUSE_X, MOUSE_X}}, mCharacter, (void* (Object::*)(float))&Ground_Player::RotateLocalAxisY);
}