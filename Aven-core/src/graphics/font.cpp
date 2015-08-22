#include "font.h"

namespace aven
{
	namespace graphics
	{
		Font::Font(std::string name, std::string filename, int size)
			: m_Name(name), m_Filename(filename), m_Size(size), m_Scale(math::Vec2(1, 1))
		{
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, filename.c_str());
			AVEN_ASSERT(m_FTFont, "Failed to load font '", filename.c_str(), "'!");
		}

		void Font::setScale(float x, float y)
		{
			m_Scale = math::Vec2(x, y);
		}
	}
}