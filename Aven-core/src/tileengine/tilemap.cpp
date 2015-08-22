#include "tilemap.h"
#include "../graphics/texture_manager.h"
#include "../graphics/layers/group.h"
#include <memory>

namespace aven
{
	namespace tileengine
	{
		TileMap::TileMap(int width, int height, Tileset* tileset) :
			m_Width(width), m_Height(height)
		{
			m_Tileset = tileset;

			m_Tiles = new int[m_Width * m_Height];
			
			for (int y = 0; y < m_Height; y++)
			{
				for (int x = 0; x < m_Width; x++)
				{
					int tileIndex = (x + y * (m_Width + 1)) % 4;
					m_Tiles[x + y * m_Width] = tileIndex;
				}
			}
		}

		void TileMap::submit(Layer* layer, float scale)
		{
			for (int y = 0; y < m_Height; y++)
			{
				for (int x = 0; x < m_Width; x++)
				{
					int tileIndex = (x + y * m_Width);

					m_Tileset = new Tileset(m_Tileset->getName(), m_Tileset->getTexture(), m_Tileset->getTileWidth(), m_Tileset->getTileHeight());

					Sprite* tile = m_Tileset->getTile(m_Tiles[tileIndex]);
					tile->size = tile->size * scale;
					tile->position = math::Vec2(x * m_Tileset->getTileWidth() * scale, y * m_Tileset->getTileHeight() * scale);
					
					layer->add(tile);
				}
			}			
		}
	}
}