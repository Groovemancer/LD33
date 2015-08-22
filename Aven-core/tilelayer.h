#pragma once

#include "src/graphics/layers/layer.h"
#include "src/graphics/batch_renderer2D.h"

class TileLayer : public aven::graphics::Layer
{
public:
	TileLayer(aven::graphics::Shader* shader);
	~TileLayer();
};