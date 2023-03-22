#include "IPCAPI.h"

bool Pipe_API::Create_Server(CPipeServer** ppObj)
{
	bool nRet = false;
	if (ppObj)
	{
		(*ppObj) = new CPipeServer();
		nRet = true;
	}

	return nRet;
}

bool Pipe_API::Create_Client(CPipeClient** ppObj)
{
	bool nRet = false;
	if (ppObj)
	{
		(*ppObj) = new CPipeClient();
		nRet = true;
	}

	return nRet;
}

bool Pipe_API::Delete_Server(CPipeServer** ppObj)
{
	bool nRet = false;
	if (ppObj)
	{
		delete (*ppObj);
		(*ppObj) = nullptr;
		nRet = true;
	}

	return nRet;
}

bool Pipe_API::Delete_Client(CPipeClient** ppObj)
{
	bool nRet = false;
	if (ppObj)
	{
		delete (*ppObj);
		(*ppObj) = nullptr;
		nRet = true;
	}

	return nRet;
}
