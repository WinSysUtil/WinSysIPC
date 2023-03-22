#include "PipeServer.h"


CPipeServer::CPipeServer()
{
}

bool CPipeServer::Create(std::wstring& wstrPipeName)
{
    bool nRet = true;
    std::wstring wstrPipePath(L"\\\\.\\pipe\\");
    wstrPipePath.append(wstrPipeName);

    m_pipe = CreateNamedPipeW(wstrPipePath.c_str(),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        1024 * 16,
        1024 * 16,
        0,
        NULL);

    
    if (m_pipe == INVALID_HANDLE_VALUE)
    {
        nRet = false;
    }

    return nRet;
}

void CPipeServer::Start()
{
    char buffer[1024];
    while (true) {
        DWORD bytesRead;
        if (ReadFile(m_pipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead)
        {
            std::string message(buffer, bytesRead);
            MessageReceivedCallback(message);
        }
        else
        {
            ErrorHandler();
        }
    }
}

void CPipeServer::SetMessageReceivedCallback(const std::function<void(const std::string&)>& callback)
{
    m_messageReceivedCallback = callback;
}

void CPipeServer::ErrorHandler()
{
    const DWORD dwErr = ::GetLastError();
    switch (dwErr)
    {
    case ERROR_PIPE_LISTENING:
    case ERROR_BROKEN_PIPE:
        DisconnectNamedPipe(m_pipe);
        ConnectNamedPipe(m_pipe, NULL);
    default:
        break;
    }
}

void CPipeServer::MessageReceivedCallback(const std::string& message)
{
    if (m_messageReceivedCallback) {
        m_messageReceivedCallback(message);
    }
}