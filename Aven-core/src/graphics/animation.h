#pragma once

#include <vector>
#include <string>

namespace aven
{
	namespace graphics
	{
		class Sprite;
		class Animation
		{
		private:
			std::string m_Name;
			std::vector<int> m_Frames;

			unsigned int m_CurrentFrame;
			
			bool m_Loop;
			bool m_Playing;
			bool m_Paused;

			float m_FrameCounter;
			float m_Fps;

		public:
			Animation(std::string name, std::vector<int> frames, float fps, bool loop = false);

			bool update();
			void play();
			void pause();
			void stop();

			inline bool isPlaying() const { return m_Playing; }
			inline std::string getName() const { return m_Name; }

			int getCurrentFrame() const { return m_Frames[m_CurrentFrame]; }
		};
	}
}