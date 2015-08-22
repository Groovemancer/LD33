#include <aven.h>
#include "tileengine/tileset.h"
#include "tileengine/tilemap.h"

using namespace aven;
using namespace graphics;
using namespace tileengine;

class Game : public Aven
{
private:
	Window* window;
	Layer* layer;
	Label* fps;

	float scale = 3.0f;

	Tileset* tileset;
	TileMap* tilemap;

	Sprite* sprite;
	Sprite* fighterSprite;

	int dir = 0;
	Animation* a_fighterIdleDown;
	Animation* a_fighterIdleUp;
	Animation* a_fighterIdleLeft;
	Animation* a_fighterIdleRight;
	Animation* a_fighterWalkDown;
	Animation* a_fighterWalkUp;
	Animation* a_fighterWalkLeft;
	Animation* a_fighterWalkRight;

	Shader* shader;

	math::Vec2 viewport;

public:
	Game()
	{

	}

	~Game()
	{
		delete layer;
		delete tileset;
		delete tilemap;
	}

	void init() override
	{
		window = createWindow("LD #33", 1600, 900);
		viewport = math::Vec2(1920, 1080);

		FontManager::get()->setScale(window->getWidth() / viewport.x, window->getHeight() / viewport.y);
		shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
		layer = new Layer(new BatchRenderer2D(), shader, math::Mat4::orthographic(0.0f, viewport.x, 0.0f, viewport.y, -1.0f, 1.0f));
		//shader->setUniform4f("colour", math::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

		// Render first, background
		Sprite* sprite1 = new Sprite(0, 0, viewport.x, viewport.y, math::Vec4(0.0f, 1.0f, 1.0f, 1.0f));
		layer->add(sprite1);
		
		tileset = new Tileset("tileset00", TextureManager::add("tileset00", "res/textures/tileset00.png"), 32, 32);
		tilemap = new TileMap(20, 12, tileset);
		tilemap->submit(layer, scale);

		/*
		//Sprite* ss_tileset00 = new Sprite(TextureManager::add("tileset00", "res/textures/tileset00.png"));
		//ss_tileset00->sliceSprite(32, 32);
		//ss_tileset00->size = math::Vec2(32 * scale, 32 * scale);
		
		for (int y = 0; y < 12; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				int index = (x + y * 21) % 4;
				//Sprite* tile = new Sprite(TextureManager::add("tileset00", "res/textures/tileset00.png"));
				//tile->sliceSprite(32, 32);
				//tile->getSlice(index);
				//tile->size = math::Vec2(32 * scale, 32 * scale);

				tileset00 = new Tileset("tileset00", TextureManager::add("tileset00", "res/textures/tileset00.png"), 32, 32);
				
				Sprite* tile = tileset00->getTile(index);
				tile->size = tile->size * scale;
				//Sprite* tile = new Sprite(*ss_tileset00->getSlice(index));
				tile->position = math::Vec2(x * tileset00->getTileWidth() * scale, y * tileset00->getTileHeight() * scale);

				layer->add(tile);
			}
		}
		*/
		
		fighterSprite = new Sprite(TextureManager::add("001-Fighter03", "res/textures/001-Fighter01.png"));
		fighterSprite->sliceSprite(32, 48);
		fighterSprite->getSlice(1, 1);		
		fighterSprite->size = math::Vec2(32 * scale, 48 * scale);
		layer->add(fighterSprite);

		float a_fps = 8;
		a_fighterIdleDown = new Animation("Fighter001-idleDown", { 0 }, a_fps, true);
		a_fighterIdleLeft = new Animation("Fighter001-idleLeft", { 4 }, a_fps, true);
		a_fighterIdleRight = new Animation("Fighter001-idleRight", { 8 }, a_fps, true);
		a_fighterIdleUp = new Animation("Fighter001-idleUp", { 12 }, a_fps, true);
		a_fighterWalkDown = new Animation("Fighter001-walkDown", { 1, 2, 3, 0 }, a_fps, true);
		a_fighterWalkLeft = new Animation("Fighter001-walkLeft", { 5, 6, 7, 4 }, a_fps, true);
		a_fighterWalkRight = new Animation("Fighter001-walkRight", { 9, 10, 11, 8 }, a_fps, true);
		a_fighterWalkUp = new Animation("Fighter001-walkUp", { 13, 14, 15, 12 }, a_fps, true);
		fighterSprite->setAnimation(a_fighterIdleDown)->play();

		Group* fpsGroup = new Group(math::Mat4::translation(math::Vec3(8.0f, viewport.y - 70, 0.0f)));
		layer->add(fpsGroup);
		Sprite* fps_bg = new Sprite(0, 0, 192, 56, math::Vec4(0.3f, 0.3f, 0.3f, 0.75f));
		fpsGroup->add(fps_bg);
		fps = new Label("", 4, 14, 0xff00ff00);
		fpsGroup->add(fps);		

		//audio::SoundManager::add(new audio::Sound("sanctified", "res/sanctified.ogg"))->play();
		//audio::SoundManager::get("sanctified")->setGain(0.1f);
	}

	void tick() override
	{
		fps->text = std::to_string(getFPS()) + " fps";
		AVEN_WARN(getUPS(), " ups, ", getFPS(), " fps");
	}

	void update() override
	{
		float speed = 8;
		bool moving = false;
		float dx = 0, dy = 0;

		fighterSprite->updateAnim();

		if (window->isKeyPressed(GLFW_KEY_ESCAPE))
		{
			window->exit();
		}

		if (window->isKeyTyped(GLFW_KEY_V))
		{
			window->setVsync(!window->isVsync());
		}

		if (window->isKeyPressed(GLFW_KEY_DOWN))
		{
			dir = 0;
			dy = -1;
		}
		else if (window->isKeyPressed(GLFW_KEY_UP))
		{
			dir = 3;
			dy = 1;
		}

		if (window->isKeyPressed(GLFW_KEY_LEFT))
		{
			dir = 1;
			dx = -1;
		}
		else if (window->isKeyPressed(GLFW_KEY_RIGHT))
		{
			dir = 2;
			dx = 1;
		}

		if (dx != 0 || dy != 0)
		{
			moving = true;

			if (dx != 0 && dy != 0)
			{
				math::Vec2 move = math::Vec2(dx, dy);
				move = move.normalize();

				fighterSprite->position.x += move.x * speed;
				fighterSprite->position.y += move.y * speed;
			}
			else
			{
				fighterSprite->position.x += dx * speed;
				fighterSprite->position.y += dy * speed;
			}
		}

		if (dir == 0)
		{
			if (moving)
				fighterSprite->setAnimation(a_fighterWalkDown)->play();
			else
				fighterSprite->setAnimation(a_fighterIdleDown)->play();
		}
		else if (dir == 1)
		{
			if (moving)
				fighterSprite->setAnimation(a_fighterWalkLeft)->play();
			else
				fighterSprite->setAnimation(a_fighterIdleLeft)->play();
		}
		else if (dir == 2)
		{
			if (moving)
				fighterSprite->setAnimation(a_fighterWalkRight)->play();
			else
				fighterSprite->setAnimation(a_fighterIdleRight)->play();
		}
		else if (dir == 3)
		{
			if (moving)
				fighterSprite->setAnimation(a_fighterWalkUp)->play();
			else
				fighterSprite->setAnimation(a_fighterIdleUp)->play();
		}

		//fighterSprite = fighterSprite->getAnim()->getCurrentFrame();
		/*
		shader->setUniform3f("falloff", math::Vec3(0.4f, 6.0f, 20.0f));
		math::Vec2 mouse = window->getMousePosition();
		math::Vec2 scale;
		scale.x = viewport.x / window->getWidth();
		scale.y = viewport.y / window->getHeight();
		shader->setUniform2f("light_pos", math::Vec2(
		(mouse.x * scale.x * 2 - viewport.x) / viewport.x,
		(viewport.y - mouse.y * scale.y * 2) / viewport.y));
		//shader->setUniform2f("light_pos", math::Vec2((mouse.x * 2 - window->getWidth()) / window->getWidth(), (window->getHeight() - mouse.y * 2) / window->getHeight()));
		*/
	}

	void render() override
	{
		layer->render();
	}
};

int main()
{
	Game game;
	game.start();
	return 0;
}