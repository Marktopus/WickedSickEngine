#include "GraphicsPrecompiled.h"
#include "ShaderCallbacks.h"

#include "System/Graphics.h"
#include "Core/CoreInterface.h"
#include "Math/MathInterface.h"
#include "Camera/Camera.h"

namespace WickedSick
{
  void ColorShaderCallback(Graphics* gSys, ModelComponent* comp, std::vector<ParamPasser>& params)
  {
    Matrix4 modelToWorld;
    Camera* camera = gSys->GetCamera();
    Transform* tr = (Transform*) comp->GetSibling(CT_Transform);

    modelToWorld.Identity();



    Matrix4 rotate = modelToWorld.GetRotatedXYZ(tr->GetRotation());
    Matrix4 scale = modelToWorld.GetScaled(tr->GetScale());
    Matrix4 translate = modelToWorld.GetTranslated(tr->GetPosition());

    modelToWorld = translate * rotate * scale;

    Matrix4 worldToClip = gSys->GetProjection() * camera->GetViewMatrix();
    Vector3 cameraPos = camera->GetPosition();
    Vector3 lightDir = Vector3(-1.0f, -1.0f, -1.0f);


    params.push_back(std::move(ParamPasser("LightBuffer", "modelToWorld", &modelToWorld, sizeof(modelToWorld))));
    params.push_back(std::move(ParamPasser("LightBuffer", "worldToClip", &worldToClip, sizeof(worldToClip))));
    params.push_back(std::move(ParamPasser("LightBuffer", "lightDir", &lightDir, sizeof(lightDir))));
    params.push_back(std::move(ParamPasser("LightBuffer", "cameraPos", &cameraPos, sizeof(cameraPos))));
  }

  void WireframeShaderCallback(Graphics* gSys, ModelComponent* comp, std::vector<ParamPasser>& params)
  {
    Matrix4 modelToWorld;
    Camera* camera = gSys->GetCamera();
    Transform* tr = (Transform*) comp->GetSibling(CT_Transform);

    modelToWorld.Identity();



    Matrix4 rotate = modelToWorld.GetRotatedXYZ(tr->GetRotation());
    Matrix4 scale = modelToWorld.GetScaled(tr->GetScale());
    Matrix4 translate = modelToWorld.GetTranslated(tr->GetPosition());

    modelToWorld = translate * rotate * scale;
    
    Matrix4 worldToClip = gSys->GetProjection() * camera->GetViewMatrix();
    Matrix4 modelToClip = worldToClip * modelToWorld;
    Vector4 color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);


    params.push_back(ParamPasser("DrawBuffer", "modelToClip", &modelToClip, sizeof(modelToClip)));
    params.push_back(ParamPasser("DrawBuffer", "color", &color, sizeof(color)));
  }

}


