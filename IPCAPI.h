#pragma once
#include "PipeClient.h"
#include "PipeServer.h"

#ifdef WINSYSIPC_EXPORTS
#define WINSYSIPC_API __declspec(dllexport)
#else
#define WINSYSIPC_API __declspec(dllimport)
#endif

namespace Pipe_API {
	WINSYSIPC_API bool Create_Server(CPipeServer** ppObj);
	WINSYSIPC_API bool Create_Client(CPipeClient** ppObj);

	WINSYSIPC_API bool Delete_Server(CPipeServer** ppObj);
	WINSYSIPC_API bool Delete_Client(CPipeClient** ppObj);
}
