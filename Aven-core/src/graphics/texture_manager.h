#pragma once

#include <vector>
#include "texture.h"

namespace aven
{
	namespace graphics
	{
		class TextureManager
		{
		private:
			static std::vector<Texture*> m_Textures;
		public:
			static Texture* add(Texture* texture);
			static Texture* add(const std::string& name, const std::string& filename);
			static Texture* get(const std::string& name);
			static void clean();
		private:
			TextureManager() { }
		};
	}
}