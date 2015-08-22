#include "tileset.h"
#include <memory>

namespace aven
{
	namespace tileengine
	{
		Tileset::Tileset(std::string name, Texture* spriteSheet, int tileWidth, int tileHeight) :
			m_Name(name), m_TileWidth(tileWidth), m_TileHeight(tileHeight), m_Texture(spriteSheet)
		{
			m_SpriteSheet = new Sprite(spriteSheet);
			m_SpriteSheet->sliceSprite(m_TileWidth, m_TileHeight);
			m_SpriteSheet->size = math::Vec2(m_TileWidth, m_TileHeight);
		}

		Sprite* Tileset::getTile(int index)
		{
			return m_SpriteSheet->getSlice(index);
		}
	}
}