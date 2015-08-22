#pragma once

#include "../graphics/sprite.h"
#include <string>

namespace aven
{
	namespace tileengine
	{
		using namespace graphics;
		class Tileset
		{
		private:
			std::string m_Name;
			Sprite* m_SpriteSheet;
			Texture* m_Texture;

			int m_TileWidth;
			int m_TileHeight;

		public:
			Tileset() {}
			Tileset(std::string name, Texture* spriteSheet, int tileWidth, int tileHeight);

			Sprite* getTile(int index);

			inline std::string getName() const { return m_Name; }
			inline int getTileWidth() const { return m_TileWidth; }
			inline int getTileHeight() const { return m_TileHeight; }
			inline Texture* getTexture() const { return m_Texture; }
		};
	}
}