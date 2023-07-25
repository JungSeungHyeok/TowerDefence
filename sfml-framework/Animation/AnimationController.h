#pragma once
#include <SFML/Graphics.hpp>

class AnimationController
{
protected:
	std::unordered_map<std::string, AnimationClip> clips;
	std::queue<std::string> queue; // 큐 컨테이너 추가

	float speed = 1.f;
	bool isPlaying = false;

	AnimationClip* currentClip = nullptr;
	int currentFrame = -1;
	int totalFrame = 0;
	float clipDuration = 0.f;
	float accumTime = 0.f; // 갱신값

	sf::Sprite* target = nullptr;

public:
	void AddClip(const AnimationClip& newClip);
	void SetTarget(sf::Sprite* sprite) { target = sprite; };
	sf::Sprite* GetTarget() const { return target; }
	bool IsPlaying() { return isPlaying; }
	void SetSpeed(float s) { speed = s; }
	float Speed() const { return speed; }

	const std::string& GetCurrentClipId() const 
	{ 
		if (currentClip == nullptr)
			return "";
		return currentClip->id;
	}

	void Update(float dt);

	void Play(const std::string& clipid, bool clearQueue = true);
	void PlayQueue(const std::string& clipid);

	void Stop();
	void SetFrame(const AnimationFrame& frame);

	std::string GetCurrentClipId();
};

