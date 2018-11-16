#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL Stage final : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		void CreateTile(STAGE_TYPE _stage_type, int _idx_width, int _idx_height, Math::Vector2 const& _tile_size);

		std::pair<int, int> GetTileIdx(Math::Vector3 const& _position);
		Math::Vector3 GetTileCenterPosition(std::pair<int, int> const& _idx_pair) const;
		std::list<std::pair<int, int>> const& GetTileAdjacencyList(std::pair<int, int> const& _idx_pair) const;

		STAGE_TYPE stage_type() const;
		TILE_OPTION tile_option(int _x_idx, int _y_idx) const;

		void set_tile_option(int _x_idx, int _y_idx, TILE_OPTION _option);

	protected:
		Stage() = default;
		Stage(Stage const& _other);
		Stage(Stage&& _other) noexcept;
		Stage& operator=(Stage const&) = default;
		Stage& operator=(Stage&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		void _CreateRectTile();
		void _CreateIsometricTile();

		std::pair<int, int> _GetRectTileIdx(Math::Vector3 const& _position);
		std::pair<int, int> _GetIsometricTileIdx(Math::Vector3 const& _position);

		STAGE_TYPE stage_type_{};
		std::vector<std::vector<std::shared_ptr<Object>>> tile_vector_2d_{};
		Math::Vector2 stage_size_{};
		Math::Vector2 tile_size_{};
		std::pair<int, int> view_range_idx_x_{};
		std::pair<int, int> view_range_idx_y_{};
		std::vector<std::vector<std::list<std::pair<int, int>>>> tile_graph_{};
	};
}
