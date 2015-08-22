#pragma once

#include "../renderable2d.h"

namespace aven
{
	namespace graphics
	{
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_Renderables;
			math::Mat4 m_TransformationMatrix;
		public:
			Group(const math::Mat4& transform);
			~Group();
			void add(Renderable2D* renderable);
			void submit(Renderer2D* renderer) const override;

			math::Mat4& getTransformRef() { return m_TransformationMatrix; }
		};
	}
}