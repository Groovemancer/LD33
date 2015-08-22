#pragma once

#include "../renderer2d.h"
#include "../renderable2d.h"

namespace aven
{
	namespace graphics
	{
		class Layer
		{
		protected:
			Renderer2D* m_Renderer;
			std::vector<Renderable2D*> m_Renderables;
			Shader* m_Shader;
			math::Mat4 m_ProjectionMatrix;
		public:
			Layer(Renderer2D* renderer, Shader* shader, math::Mat4 projectionMatrix);
			virtual ~Layer();
			virtual void add(Renderable2D* renderable); // TODO: Return Renderable2D*
			virtual void render();

			inline const std::vector<Renderable2D*>& getRenderables() const { return m_Renderables; };
		};
	}
}