#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;
	std::function<void()> action; // 기본값이 널이라 널ptr 딱히 할필요없다
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopType;

	int fps;

	bool LoadFromFile(const std::string path);
};
