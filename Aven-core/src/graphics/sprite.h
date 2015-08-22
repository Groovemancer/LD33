#pragma once

#include "renderable2d.h"
#include "animation.h"

namespace aven
{
	namespace graphics
	{
		class Animation;
		class Sprite : public Renderable2D
		{
		private:
			int m_SubWidth, m_SubHeight;
			Animation* m_Animation;

		public:
			math::Vec3& position;
			math::Vec2& size;

		public:
			Sprite(Texture* texture);
			Sprite(float x, float y, Texture* texture);
			Sprite(float x, float y, float width, float height, unsigned int color);
			Sprite(float x, float y, float width, float height, math::Vec4 color);
			Sprite(float x, float y, float width, float height, Texture* texture);
			Sprite(float x, float y, float width, float height, float srcX, float srcY, float srcWidth, float srcHeight, Texture* texture);

			void setUV(std::vector<math::Vec2> uv);

			void sliceSprite(int subWidth, int subHeight);
			Sprite* getSlice(int index);
			Sprite* getSlice(int x, int y);

			Animation* setAnimation(Animation* anim);
			void updateAnim();

			inline Animation* getAnim() const { return m_Animation; }
		};
	}
}