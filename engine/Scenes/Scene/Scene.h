#pragma once

#include <vector>
using namespace std;

#include "engine/Objects/Object/Object.h"
#include "engine/Objects/ObjectManager/ObjectManager.h"
#include "engine/ShaderHandlers/ShaderManager/ShaderManager.h"
#include "engine/Utils/Interfaces/ITickable.h"


class Scene : public Object, public ITickable
{
public:
    virtual ~Scene();

public:
    virtual void LoadScene() = 0;
    virtual void UnloadScene();

    virtual void Update(const float _deltaTime) override;
    virtual void LateUpdate(const float _deltaTime) override;
};