#include "sprite.h"

namespace aven
{
	namespace graphics
	{
		Sprite::Sprite(Texture* texture)
			: Renderable2D(math::Vec3(0, 0, 0), math::Vec2(texture->getWidth(), texture->getHeight()), 0xffffffff), position(m_Position), size(m_Size)
		{
			m_Texture = texture;
		}
		
		Sprite::Sprite(float x, float y, Texture* texture)
			: Renderable2D(math::Vec3(x, y, 0), math::Vec2(texture->getWidth(), texture->getHeight()), 0xffffffff), position(m_Position), size(m_Size)
		{
			m_Texture = texture;
		}

		Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
			: Renderable2D(math::Vec3(x, y, 0), math::Vec2(width, height), color), position(m_Position), size(m_Size)
		{

		}

		Sprite::Sprite(float x, float y, float width, float height, math::Vec4 color)
			: Renderable2D(math::Vec3(x, y, 0), math::Vec2(width, height), 0), position(m_Position), size(m_Size)
		{
			setColor(color);
		}

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(math::Vec3(x, y, 0), math::Vec2(width, height), 0xffffffff), position(m_Position), size(m_Size)
		{
			m_Texture = texture;
		}

		Sprite::Sprite(float x, float y, float width, float height, float srcX, float srcY, float srcWidth, float srcHeight, Texture* texture)
			: Renderable2D(math::Vec3(x, y, 0), math::Vec2(width, height), 0xffffffff), position(m_Position), size(m_Size)
		{
			m_Texture = texture;
			std::vector<math::Vec2> uv;
			uv.push_back(math::Vec2(srcX / m_Texture->getWidth(), srcY / m_Texture->getHeight()));
			uv.push_back(math::Vec2(srcX / m_Texture->getWidth(), (srcY + srcHeight) / m_Texture->getHeight()));
			uv.push_back(math::Vec2((srcX + srcWidth) / m_Texture->getWidth(), (srcY + srcHeight) / m_Texture->getHeight()));
			uv.push_back(math::Vec2((srcX + srcWidth) / m_Texture->getWidth(), srcY / m_Texture->getHeight()));			
			m_UV = uv;
		}

		void Sprite::setUV(std::vector<math::Vec2> uv)
		{
			m_UV = uv;
		}

		void Sprite::sliceSprite(int subWidth, int subHeight)
		{
			m_SubWidth = subWidth;
			m_SubHeight = subHeight;
		}

		Sprite* Sprite::getSlice(int index)
		{
			int cols = m_Texture->getWidth() / m_SubWidth;
			int rows = m_Texture->getHeight() / m_SubHeight;
			
			float x = index % cols;
			float y = (rows - 1) - int(index / rows);
			float w = 1.0f / cols;
			float h = 1.0f / rows;
			
			std::vector<math::Vec2> uv;
			uv.push_back(math::Vec2(x / cols, y / rows));
			uv.push_back(math::Vec2(x / cols, y / rows + h));
			uv.push_back(math::Vec2(x / cols + w, y / rows + h));
			uv.push_back(math::Vec2(x / cols + w, y / rows));
			m_UV = uv;

			return this;
		}

		Sprite* Sprite::getSlice(int x, int y)
		{
			int cols = m_Texture->getWidth() / m_SubWidth;
			return getSlice(x + y * cols);
		}

		Animation* Sprite::setAnimation(Animation* anim)
		{
			m_Animation = anim;
			return m_Animation;
		}

		void Sprite::updateAnim()
		{
			// Is animation set
			if (m_Animation != NULL)
			{
				// Update, but only change frame if current frame is updated
				if (m_Animation->update())
					getSlice(m_Animation->getCurrentFrame());
			}
		}
	}
}