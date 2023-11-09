#include "World05.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

#define INTERLEAVE

namespace nc
{
    bool World05::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("scenes/scene.json");
        m_scene->Initialize();

       /* {
            auto actor = CREATE_CLASS(Actor);
            actor->name = "actor1";
            actor->transform.position = glm::vec3{ 0, 0, 0 };
            auto modelComponent = CREATE_CLASS(ModelComponent);
            modelComponent->model = std::make_shared<Model>();
            modelComponent->model->SetMaterial(GET_RESOURCE(Material, "materials/squirrel.mtrl"));
            modelComponent->model->Load("models/squirrel.glb", glm::vec3{ 0, -0.7f, 0 }, glm::vec3{ 0 }, glm::vec3{ 0.4f });
            actor->AddComponent(std::move(modelComponent));
            m_scene->Add(std::move(actor));
        }

        {
            auto actor = CREATE_CLASS(Actor);
            actor->name = "light1";
            actor->transform.position = glm::vec3{ 3, 3, 3 };
            auto lightComponent = CREATE_CLASS(LightComponent);
            lightComponent->type = LightComponent::eType::Point;
            lightComponent->color = glm::rgbColor(glm::vec3{ randomf() * 360, 1, 1 });
            lightComponent->intensity = 1;
            lightComponent->range = 20;
            lightComponent->innerAngle = 10.0f;
            lightComponent->outerAngle = 30.0f;
            actor->AddComponent(std::move(lightComponent));
            m_scene->Add(std::move(actor));
        }*/

        

        {
            for (int i = 0; i < 10; i++) {
                auto actor = CREATE_CLASS_BASE(Actor, "tree");
                actor->transform.position = glm::vec3{ randomf(-10, 10), 0, randomf(-10, 10) };
                actor->transform.scale = glm::vec3{ randomf(0.5f, 3.0f), randomf(0.5f, 3.0f), randomf(0.5f, 3.0f) };
                actor->Initialize();
                m_scene->Add(std::move(actor));
            }
        }

        return true;
    }
    
    void World05::Shutdown()
    {
    }

    void World05::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();
        //m_scene->ProcessGui();



       

        //m_transform.rotation.z += 90 * dt;

        auto actor = m_scene->GetActorByName<Actor>("ogre");


        auto material = actor->GetComponent<ModelComponent>()->material;
        material->ProcessGui();
        material->Bind();

        material = GET_RESOURCE(Material, "materials/refraction.mtrl");
        if (material) {
            ImGui::Begin("Refraction");
            
            //neat effect
            //m_refraction = 1 + std::fabs(std::sin(m_time));

            ImGui::DragFloat("IOR", &m_refraction, 0.01f, 1, 3);
            auto program = material->GetProgram();
            program->Use();
            program->SetUniform("ior", m_refraction);
            
            ImGui::End();
        }
       

    /*    GLint uniform = glGetUniformLocation(m_program->m_program, "model");
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(model));*/

       /* glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
        material->GetProgram()->SetUniform("view", view);*/
      /*  uniform = glGetUniformLocation(m_program->m_program, "view");
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(view));*/

       /* glm::mat4 projection = glm::perspective(glm::radians(70.0f), ENGINE.Instance().GetSystem<Renderer>()->GetWidth() / (float)ENGINE.Instance().GetSystem<Renderer>()->GetHeight(), 0.01f, 100.0f);
       material->GetProgram()->SetUniform("projection", projection);*/
       /* uniform = glGetUniformLocation(m_program->m_program, "projection");
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(projection));*/

        // get camera component
        


        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World05::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

       
        // render
        
        //will only draw a wire mesh
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        //will draw the full model
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_scene->Draw(renderer);

        ENGINE.GetSystem<Gui>()->Draw();


        // post-render
        renderer.EndFrame();
    }
}
