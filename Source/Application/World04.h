#pragma once
#include "Framework/World.h"
#include "Core/Math/Vector2.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc
{
	class World04 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time = 0;
		float m_speed = 10.0f;

		Transform m_transform;

		glm::vec3 m_aColor = glm::vec3(0.2, 0.2, 0.2);
		glm::vec3 m_lColor = glm::vec3(1, 1, 1);
		glm::vec3 m_lPosition = glm::vec3(0, 8, 0);

		res_t<VertexBuffer> m_vertexBuffer;
		res_t<Program> m_program;
		res_t<Texture> m_texture;
		res_t<Material> m_material;
		res_t<Model> m_model;

	};
}