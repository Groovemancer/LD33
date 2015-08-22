#include "texture_manager.h"

namespace aven
{
	namespace graphics
	{
		std::vector<Texture*> TextureManager::m_Textures;

		Texture* TextureManager::add(Texture* texture)
		{
			for (Texture* t : m_Textures)
			{
				if (t->getName() == texture->getName())
				{
					delete texture;
					return t;
				}
			}
			m_Textures.push_back(texture);
			return texture;
		}

		Texture* TextureManager::add(const std::string& name, const std::string& filename)
		{
			Texture* texture = new Texture(name, filename);
			for (Texture* t : m_Textures)
			{
				if (t->getName() == name)
				{
					delete texture;
					return t;
				}
			}
			m_Textures.push_back(texture);
			return texture;
		}

		Texture* TextureManager::get(const std::string& name)
		{
			for (Texture* texture : m_Textures)
			{
				if (texture->getName() == name)
					return texture;
			}

			return nullptr;
		}

		void TextureManager::clean()
		{
			for (int i = 0; i < m_Textures.size(); i++)
				delete m_Textures[i];
		}
	}
}