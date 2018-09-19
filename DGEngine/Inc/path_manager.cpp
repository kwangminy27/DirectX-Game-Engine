#include "DGEngine_stdafx.h"
#include "path_manager.h"

using namespace std;
using namespace filesystem;
using namespace DG;

void PathManager::Initialize()
{
	path path_buffer = current_path();
	path_buffer.replace_filename("Bin\\");

	path_map_.insert(make_pair("RootPath", move(path_buffer)));

	try
	{

	}
	catch (exception const& _e)
	{
		cerr << _e.what() << endl;
	}
}

path const& PathManager::FindPath(string const& _tag) const
{
	auto iter = path_map_.find(_tag);

	if (iter == path_map_.end())
		throw exception{ "PathManager::FindPath" };

	return iter->second;
}

void PathManager::_Release()
{
}

void PathManager::_AddPath(string const& _tag, path const& _path, string const& _base_path_tag)
{
	if (!FindPath(_tag).empty())
		throw exception{ "PathManager::_AddPath" };

	path path_buffer = FindPath(_base_path_tag);

	if(path_buffer.empty())
		throw exception{ "PathManager::_AddPath" };

	path_buffer /= _path;

	path_map_.insert(make_pair(_tag, move(path_buffer)));
}
