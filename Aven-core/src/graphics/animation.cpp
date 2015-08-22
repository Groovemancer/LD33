#include "animation.h"

namespace aven
{
	namespace graphics
	{
		Animation::Animation(std::string name, std::vector<int> frames, float fps, bool loop)
			: m_Fps(1 / fps), m_Name(name), m_Frames(frames), m_Playing(false), m_Paused(false),
			m_CurrentFrame(0), m_Loop(loop), m_FrameCounter(0.0f)
		{
		}

		bool Animation::update()
		{
			bool updated = false;
			if (m_Playing)
			{
				// Update every frame. Framerate is 60fps, so every 1/60th per second
				m_FrameCounter -= 1.0f / 60.0f;

				if (m_FrameCounter <= 0)
				{
					m_CurrentFrame++;
					m_FrameCounter = m_Fps;
					updated = true;
				}

				if (m_CurrentFrame >= m_Frames.size())
				{
					if (m_Loop)
						m_CurrentFrame = 0;
					else
					{
						m_CurrentFrame = m_Frames.size() - 1;
						stop();
					}
				}
			}
			return updated;
		}

		void Animation::play()
		{
			m_Playing = true;
			m_Paused = false;
		}

		void Animation::pause()
		{
			if (m_Playing)
			{
				m_Paused = true;
				m_Playing = false;
			}
		}

		void Animation::stop()
		{
			m_Playing = false;
			m_Paused = false;
			m_FrameCounter = 0.0f;
			m_CurrentFrame = 0;
		}
	}
}