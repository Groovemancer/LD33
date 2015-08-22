#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "renderer2d.h"
#include "texture.h"

#include "../math/math.h"
#include "shader.h"

namespace aven
{
	namespace graphics
	{
		struct VertexData
		{
			math::Vec3 vertex;
			math::Vec2 uv;
			float tid;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			math::Vec3 m_Position;
			math::Vec2 m_Size;
			unsigned int m_Color;
			std::vector<math::Vec2> m_UV;
			Texture* m_Texture;
		protected:
			Renderable2D() : m_Texture(nullptr) { setUVDefaults(); }
		public:
			Renderable2D(math::Vec3 position, math::Vec2 size, unsigned int color)
				: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
			{ setUVDefaults(); }

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			void setColor(unsigned int color) { m_Color = color; }
			void setColor(math::Vec4& color)
			{
				int r = (int)(color.x * 255.0f);
				int g = (int)(color.y * 255.0f);
				int b = (int)(color.z * 255.0f);
				int a = (int)(color.w * 255.0f);

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const math::Vec3& getPosition() const { return m_Position; }
			inline const math::Vec2& getSize() const { return m_Size; }
			inline const unsigned int getColor() const { return m_Color; }
			inline const std::vector<math::Vec2>& getUV() const { return m_UV; }

			inline const GLuint getTID() const { return m_Texture ? m_Texture->getID() : 0; }
		private:
			void setUVDefaults()
			{
				m_UV.push_back(math::Vec2(0, 0));
				m_UV.push_back(math::Vec2(0, 1));
				m_UV.push_back(math::Vec2(1, 1));
				m_UV.push_back(math::Vec2(1, 0));
			}
		};
	}
}