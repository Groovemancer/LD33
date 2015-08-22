#pragma once

#include <vector>
#include <avengl.h>
#include "font.h"
#include "../math/math.h"

namespace aven
{
	namespace graphics
	{
		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<math::Mat4> m_TransformationStack;
			const math::Mat4* m_TransformationBack;
		protected:
			Renderer2D()
			{
				m_TransformationStack.push_back(math::Mat4::identity());
				m_TransformationBack = &m_TransformationStack.back();
			}
		public:
			void push(const math::Mat4& matrix, bool override = false)
			{
				if (override)
					m_TransformationStack.push_back(matrix);
				else
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

				m_TransformationBack = &m_TransformationStack.back();
			}

			void pop()
			{
				// TODO: Add to log!
				if (m_TransformationStack.size() > 1)
					m_TransformationStack.pop_back();

				m_TransformationBack = &m_TransformationStack.back();
			}

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const std::string& text, const math::Vec3& position, const Font& font, unsigned int color) {}
			virtual void end() {}
			virtual void flush() = 0;
		};
	}
}