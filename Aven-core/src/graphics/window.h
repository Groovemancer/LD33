#pragma once

#include <iostream>

#include <avengl.h>

#include "../math/vec2.h"
#include "font_manager.h"
#include "texture_manager.h"
#include "../audio/sound_manager.h"

namespace aven
{

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	namespace graphics
	{
		class Window
		{
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_KeyState[MAX_KEYS];
			bool m_KeyTyped[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			bool m_MouseState[MAX_BUTTONS];
			bool m_MouseClicked[MAX_BUTTONS];
			
			math::Vec2 m_MousePosition;
			bool m_Vsync;
		public:
			Window(const char *title, int width, int height);
			~Window();
			void update();
			void updateInput();
			void clear() const;
			bool closed() const;
			void exit() const;

			inline int getWidth() const { return m_Width; }
			inline int getHeight() const { return m_Height; }

			bool isKeyPressed(unsigned int keyCode) const;
			bool isKeyTyped(unsigned int keyCode) const;			
			bool isMouseButtonPressed(unsigned int button) const;
			bool isMouseButtonClicked(unsigned int button) const;
			const math::Vec2& getMousePosition() const;

			void setVsync(bool enabled);
			bool isVsync() const { return m_Vsync; }
		private:
			bool init();
			friend void window_resize(GLFWwindow *window, int width, int height);
			friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}