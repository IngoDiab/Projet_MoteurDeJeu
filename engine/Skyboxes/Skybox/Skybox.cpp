#include "Skybox.h"
#include "engine/FilesPath/FilesPath.h"
#include "engine/Skyboxes/Mesh/SkyboxMesh.h"
#include "engine/Skyboxes/ShaderHandler/SkyboxShaderHandler.h"
#include "engine/Skyboxes/Material/SkyboxMaterial.h"
#include "engine/Camera/Camera/Camera.h"

Skybox::Skybox()
{
    mMesh = new SkyboxMesh();
    mMaterial = new SkyboxMaterial(SKYBOX_VERTEX, SKYBOX_FRAG);
}

Skybox::~Skybox()
{
    delete mMesh;
    delete mMaterial;
}

void Skybox::Draw(Camera* _renderingCamera)
{
    if(!_renderingCamera) return;
    //Calculate VP
    const mat4& _viewMatrix = _renderingCamera->GetViewMatrix();
    const mat4& _projMatrix = _renderingCamera->GetProjectionMatrix();

    //Use Material
    glUseProgram(mMaterial->GetShader()->GetShaderHandler());
    mMaterial->UseMaterial(mat4(1.0), _viewMatrix, _projMatrix);

    //Draw
    mMesh->DrawMesh();
}

void Skybox::ChangeSkybox(const string& _path, const string& _format)
{
    if(mMaterial) mMaterial->ChangeSkyboxTextures(_path, _format);
}