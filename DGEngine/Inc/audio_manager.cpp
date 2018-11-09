#include "DGEngine_stdafx.h"
#include "audio_manager.h"

#include "path_manager.h"

using namespace filesystem;
using namespace DG;
using namespace DirectX;

std::shared_ptr<DirectX::SoundEffect> AudioManager::sound_effect_nullptr_{};
std::shared_ptr<DirectX::SoundEffectInstance> AudioManager::sound_effect_instance_nullptr_{};

void AudioManager::Initialize()
{
	try
	{
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		AUDIO_ENGINE_FLAGS audio_engine_flags = AudioEngine_Default;
#ifdef _DEBUG
		audio_engine_flags =  audio_engine_flags | AudioEngine_Debug;
#endif
		audio_engine_ = std::make_unique<AudioEngine>(audio_engine_flags);

		CreateSoundEffect("town1", L"town1.wav", SOUND_PATH);
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "AudioManager::Initialize" << std::endl;
	}
}

void AudioManager::Update()
{
	audio_engine_->Update();
}

void AudioManager::Suspend()
{
	audio_engine_->Suspend();
}

void AudioManager::Resume()
{
	audio_engine_->Resume();
}

std::shared_ptr<SoundEffect> const& AudioManager::FindSoundEffect(std::string const& _tag) const
{
	auto iter = sound_effect_map_.find(_tag);

	if (iter == sound_effect_map_.end())
		return sound_effect_nullptr_;

	return iter->second;
}

std::shared_ptr<SoundEffectInstance> const& AudioManager::FindSoundEffectInstance(std::string const& _tag) const
{
	auto iter = sound_effect_instance_map_.find(_tag);

	if (iter == sound_effect_instance_map_.end())
		return sound_effect_instance_nullptr_;

	return iter->second;
}

void AudioManager::CreateSoundEffect(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag)
{
	if (FindSoundEffect(_tag))
		throw std::exception{ "AudioManager::CreateSoundEffect" };

	path path_buffer = PathManager::singleton()->FindPath(_path_tag);

	if(path_buffer.empty())
		throw std::exception{ "AudioManager::CreateSoundEffect" };

	std::wstring full_path = path_buffer.wstring() + _file_name;

	auto sound_effect = std::make_unique<SoundEffect>(audio_engine_.get(), full_path.c_str());

	sound_effect_map_.insert(make_pair(_tag, move(sound_effect)));
}

void AudioManager::AddSoundEffectInstance(std::string const& _tag, std::unique_ptr<SoundEffectInstance>& _sound_effect_instance)
{
	sound_effect_instance_map_.insert(make_pair(_tag, std::move(_sound_effect_instance)));
}

void AudioManager::RemoveSoundEffectInstance(std::string const& _tag)
{
	auto iter = sound_effect_instance_map_.find(_tag);

	if (iter != sound_effect_instance_map_.end())
		sound_effect_instance_map_.erase(_tag);
}

void AudioManager::_Release()
{
	CoUninitialize();
}
