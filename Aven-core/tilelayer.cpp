#include "tilelayer.h"

TileLayer::TileLayer(aven::graphics::Shader* shader)
	: Layer(new aven::graphics::BatchRenderer2D(), shader, aven::math::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
}

TileLayer::~TileLayer()
{
}