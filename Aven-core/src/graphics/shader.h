#pragma once

#include <iostream>
#include <vector>

#include <avengl.h>

#include "../math/math.h"
#include "../utils/fileutils.h"

namespace aven
{
	namespace graphics
	{
		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char *m_VertPath;
			const char *m_FragPath;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();
			
			void setUniform1f(const GLchar* name, float value);
			void setUniform1fv(const GLchar* name, float* value, int count);
			void setUniform1i(const GLchar* name, int value);
			void setUniform1iv(const GLchar* name, int* value, int count);
			void setUniform2f(const GLchar* name, const math::Vec2& vector);
			void setUniform3f(const GLchar* name, const math::Vec3& vector);
			void setUniform4f(const GLchar* name, const math::Vec4& vector);
			void setUniformMat4(const GLchar* name, const math::Mat4& matrix);

			void enable() const;
			void disable() const;
		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};
	}
}