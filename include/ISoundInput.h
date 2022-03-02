#pragma once
#include <functional>

using OnVoiceCallback = std::function<void(const void* buffer, int size, float micLevel)>;
using OnRawVoiceCb = std::function<void(const float* buffer, float micLevel)>;

class ISoundInput
{
public:
	virtual ~ISoundInput() = default;

	virtual bool EnableInput() = 0;
	virtual bool DisableInput() = 0;
	virtual void ChangeMicGain(float gain) = 0;
	virtual bool ChangeDevice(char* deviceName) = 0;
	virtual void RegisterCallback(OnVoiceCallback callback) = 0;
	virtual void RegisterRawCallback(OnRawVoiceCb callback) = 0;
};
