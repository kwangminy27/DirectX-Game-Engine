#pragma once

#include "singleton.h"

namespace DG
{
	class PathManager final : public Singleton<PathManager>
	{
		friend class Singleton<PathManager>;
	public:
		void Initialize();
		std::filesystem::path const& FindPath(std::string const& _tag) const;

	private:
		PathManager() = default;
		PathManager(PathManager const&) = delete;
		PathManager(PathManager&&) noexcept = delete;
		PathManager& operator=(PathManager const&) = delete;
		PathManager& operator=(PathManager&&) noexcept = delete;

		virtual void _Release() override;

		void _AddPath(std::string const& _tag, std::filesystem::path const& _path, std::string const& _base_path_tag = "RootPath");

		std::filesystem::path path_nullptr_{};
		std::unordered_map<std::string, std::filesystem::path> path_map_{};
	};
}