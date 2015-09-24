#include "ObjectFactoryPrecompiled.h"
#include "ObjectFactory.h"

#include "EventSystem/EventSystemInterface.h"
#include "Core/System/System.h"

#include "Components/ComponentFactory.h"

#include "Components/ComponentManager.h"

#include "Graphics/GraphicsInterface.h"


namespace WickedSick
{

  OBJECTFACTORYDLL_API ObjectFactory::ObjectFactory() : objects_created_(0),
                                                        comp_manager_(nullptr),
                                                        System(ST_ObjectFactory)
  {
  }

  OBJECTFACTORYDLL_API ObjectFactory::~ObjectFactory()
  {

  }

  OBJECTFACTORYDLL_API void ObjectFactory::Initialize()
  {
    comp_manager_ = new ComponentManager();
  }
  
  OBJECTFACTORYDLL_API bool ObjectFactory::Load()
  {
    

    return true;
  }
  
  OBJECTFACTORYDLL_API bool ObjectFactory::Reload()
  {
    return true;
  }
  
  OBJECTFACTORYDLL_API void ObjectFactory::Update(float dt)
  {
    comp_manager_->Update(dt);
    return;
    for (auto& it : game_objects_)
    {
      Transform* tr = (Transform*)it.val->GetComponent(CT_Transform);
      Vector3 rot = tr->GetRotation();
      rot.y += 0.01f;
      //rot.x -= 0.01f;
      //rot.z += 0.05f;
      tr->SetRotation(rot);
    }
  }

  OBJECTFACTORYDLL_API void ObjectFactory::ReceiveMessage(Event * msg)
  {

  }

  OBJECTFACTORYDLL_API GameObject* ObjectFactory::CloneArchetype(const std::string& name)
  {
    GameObject* newObject = object_factory_.Make(name);
    
    const char* names[] = {
#define RegisterComponentType(x) #x,
#include "Core/GameObject/ComponentTypes.h"
#undef RegisterComponentType
    };
    newObject->AddComponent(comp_manager_->CreateComponent(names[0], newObject));
    for (int i = 1; i < CT_Count; ++i)
    {
      newObject->AddComponent(comp_manager_->CreateComponent(names[i], name, newObject));
    }
    newObject->SetID(objects_created_++);
    game_objects_.insert(newObject->GetID(), newObject);
    newObject->Activate();
    newObject->SetArchetypeName(name);
    newObject->Initialize();
    return newObject;
  }

  OBJECTFACTORYDLL_API GameObject* ObjectFactory::MakeBlank()
  {
    return object_factory_.MakeBlank();
  }

  OBJECTFACTORYDLL_API ComponentManager * ObjectFactory::GetComponentManager()
  {
    return comp_manager_;
  }

  OBJECTFACTORYDLL_API void ObjectFactory::CreateArchetypes()
  {
    ComponentFactory<ModelComponent>* modelFactory = (ComponentFactory<ModelComponent>*)comp_manager_->GetFactory("ModelComponent");

    modelFactory->AddArchetype("bunny", Archetype<ModelComponent>("bunny"));
    Archetype<ModelComponent>& bunnyCompType = modelFactory->GetArchetype("bunny");
    ModelComponent& bunnyModelComp = bunnyCompType.GetBase();
    bunnyModelComp.SetModel("bunny");



    WickedSick::Graphics* gSys = (WickedSick::Graphics*)Engine::GetCore()->GetSystem(ST_Graphics);

    object_factory_.AddArchetype("bunny", Archetype<GameObject>("bunny") );
    Archetype<GameObject>& bunny = object_factory_.GetArchetype("bunny");
    GameObject& bunnyObject = bunny.GetBase();
    Component* bunnyComp = comp_manager_->CreateComponent("ModelComponent", 
                                                          "bunny", 
                                                          &bunnyObject);
    bunnyObject.AddComponent(bunnyComp);


    modelFactory->AddArchetype("box", Archetype<ModelComponent>("box"));
    Archetype<ModelComponent>& cubeCompType = modelFactory->GetArchetype("box");
    ModelComponent& cubeModelComp = cubeCompType.GetBase();
    cubeModelComp.SetModel("box");

    object_factory_.AddArchetype("box", Archetype<GameObject>("box") );
    Archetype<GameObject>& cube = object_factory_.GetArchetype("box");
    GameObject& cubeObject = cube.GetBase();
    Component* cubeComp = comp_manager_->CreateComponent( "ModelComponent",
                                                          "box",
                                                          &cubeObject);
    cubeObject.AddComponent(cubeComp);



    modelFactory->AddArchetype("sphere", Archetype<ModelComponent>("sphere"));
    Archetype<ModelComponent>& sphereCompType = modelFactory->GetArchetype("sphere");
    ModelComponent& sphereModelComp = sphereCompType.GetBase();
    sphereModelComp.SetModel("sphere");

    object_factory_.AddArchetype("sphere", Archetype<GameObject>("sphere"));
    Archetype<GameObject>& sphere = object_factory_.GetArchetype("sphere");
    GameObject& sphereObject = sphere.GetBase();
    Component* sphereComp = comp_manager_->CreateComponent("ModelComponent",
                                                           "sphere",
                                                           &sphereObject);
    sphereObject.AddComponent(sphereComp);


    ComponentFactory<CameraController>* controllerFactory = (ComponentFactory<CameraController>*)comp_manager_->GetFactory("CameraController");
    controllerFactory->AddArchetype("camera", Archetype<CameraController>("camera"));



    ComponentFactory<CameraComponent>* cameraFactory = (ComponentFactory<CameraComponent>*)comp_manager_->GetFactory("CameraComponent");
    cameraFactory->AddArchetype("camera", Archetype<CameraComponent>("camera"));
    Archetype<CameraComponent>& cameraCompType = cameraFactory->GetArchetype("camera");
    CameraComponent& cameraTemplateComp = cameraCompType.GetBase();
    cameraTemplateComp.SetLookAt(Vector3(0.0f,0.0f,0.0f));

    object_factory_.AddArchetype("camera", Archetype<GameObject>("camera"));
    Archetype<GameObject>& camera = object_factory_.GetArchetype("camera");
    GameObject& cameraObject = camera.GetBase();
    Component* cameraComp = comp_manager_->CreateComponent("CameraComponent",
                                                           "camera",
                                                           &cameraObject);
    cameraObject.AddComponent(cameraComp);

    Component* cameraController = comp_manager_->CreateComponent("CameraController",
                                                                 "camera",
                                                                 &cameraObject);
    cameraObject.AddComponent(cameraController);


  }

  OBJECTFACTORYDLL_API void ObjectFactory::BuildScene()
  {

    GameObject* camera = CloneArchetype("camera");
    Transform* cameraTr = (Transform*)camera->GetComponent(CT_Transform);
    cameraTr->SetRotation(0.0f, PI / 4.0f, 0.0f);
    cameraTr->SetPosition(0.0f, 1.0f, 0.5f);
    CameraComponent* cameraComp = (CameraComponent*)camera->GetComponent(CT_CameraComponent);
    cameraComp->SetLookAt(Vector3(0.0f, 0.0f, 6.0f));


    Graphics* graphics = (Graphics*)Engine::GetCore()->GetSystem(ST_Graphics);
    graphics->GetCamera()->SetSource((CameraComponent*)cameraComp);


    GameObject* bunny = CloneArchetype("bunny");
    Transform* bunnyTr = (Transform*)bunny->GetComponent(CT_Transform);
    bunnyTr->SetRotation(0.0f, PI/4.0f, 0.0f);
    bunnyTr->SetPosition(0.0f, 0.0f, 3.0f);
    bunnyTr->SetScale(10.0f);

    GameObject* box = CloneArchetype("box");
    Transform* boxTr = (Transform*)box->GetComponent(CT_Transform);
    boxTr->SetRotation(0.0f, PI / 4.0f, 0.0f);
    boxTr->SetScale(1.0f);
    boxTr->SetPosition(0.0f, 0.0f, 6.0f);


    //bunnyTr->SetScale(100.0f);
  }

}

