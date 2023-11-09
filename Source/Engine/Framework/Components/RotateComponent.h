#pragma once
#include "Framework/Actor.h"
#include "Framework/Engine.h"
#include <glm/glm/gtx/euler_angles.hpp>


namespace nc {
	class RotateComponent : public Component {
	public: 
		CLASS_DECLARATION(RotateComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void ProcessGui();

	public:
		glm::vec3 euler;
	};
}