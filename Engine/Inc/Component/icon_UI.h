#pragma once

#include "button_UI.h"

namespace DG
{
	class DG_ENGINE_DLL IconUI final : public ButtonUI
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		void AddSlot(std::shared_ptr<Object> const& _slot);

		std::shared_ptr<Object> current_slot() const;
		void set_current_slot(std::shared_ptr<Object> const& _slot);

		bool clicked_flag() const;
		void set_clicked_flag(bool _flag);

	private:
		IconUI() = default;
		IconUI(IconUI const& _other);
		IconUI(IconUI&& _other) noexcept;
		IconUI& operator=(IconUI const&) = default;
		IconUI& operator=(IconUI&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		std::list<std::weak_ptr<Object>> slot_list_{};
		std::weak_ptr<Object> current_slot_{};
		bool clicked_flag_{};
	};
}
