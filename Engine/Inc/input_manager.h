#pragma once

#include "singleton.h"

namespace DG
{
	class Object;

	struct DG_ENGINE_DLL KeyInfo
	{
		std::vector<__int8> element;
		bool push;
		bool pressed;
		bool up;
	};

	class DG_ENGINE_DLL InputManager final : public Singleton<InputManager>
	{
		friend class Singleton<InputManager>;
	public:
		void Initialize();
		void Update();
		void Render(float _time);

		bool KeyPush(std::string const& _tag) const;
		bool KeyPressed(std::string const& _tag) const;
		bool KeyUp(std::string const& _tag) const;

		std::shared_ptr<Object> const& mouse() const;
		Math::Vector3 const& mouse_client_position() const;
		Math::Vector3 const& mouse_world_position() const;
		Math::Vector3 const& mouse_displacement() const;

	private:
		InputManager() = default;
		InputManager(InputManager const&) = delete;
		InputManager(InputManager&&) noexcept = delete;
		InputManager& operator=(InputManager const&) = delete;
		InputManager& operator=(InputManager&&) noexcept = delete;

		virtual void _Release() override;

		template <typename T, typename... Types> void _AddKey(T const& _element, Types... _Args);
		template <typename... Types> void _AddKey(std::string const& _tag, Types... _Args);
		void _AddKey();

		std::unique_ptr<KeyInfo> const& _FindKey(std::string const& _tag) const;

		static std::unique_ptr<KeyInfo> key_nullptr_;
		std::unordered_map<std::string, std::unique_ptr<KeyInfo>> key_map_{};
		std::unique_ptr<KeyInfo> key_buffer_{};
		std::string key_tag_buffer_{};
		std::shared_ptr<Object> mouse_{};
		Math::Vector3 mouse_client_position_{};
		Math::Vector3 mouse_world_position_{};
		Math::Vector3 mouse_displacement_{};
		bool mouse_cursor_show_state_{};
	};

#include "input_manager.inl"

}
