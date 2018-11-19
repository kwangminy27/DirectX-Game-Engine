#include <DGNetwork_stdafx.h>
#include <server_manager.h>

int main()
{
	try
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		ServerManager::singleton()->ExcuteTCPIOCPLoop();
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "main" << std::endl;
	}

	int error = GetLastError();
	std::cout << error << std::endl;

	return 0;
}