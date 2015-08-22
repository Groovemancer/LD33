#pragma once

#include "tileset.h"
#include "../graphics/layers/layer.h"

namespace aven
{
	namespace tileengine
	{
		class TileMap
		{
		private:
			int m_Width, m_Height;
			int* m_Tiles;
						
			Tileset* m_Tileset;

		public:
			TileMap(int width, int height, Tileset* tileset);

			void submit(Layer* layer, float scale = 1.0f);

			inline int getWidth() const { return m_Width; }
			inline int getHeight() const { return m_Height; }
		};
	}
}