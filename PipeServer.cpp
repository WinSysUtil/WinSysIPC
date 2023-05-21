#include "PipeServer.h"


CPipeServer::CPipeServer() : m_bStop(FALSE)
{
}

CPipeServer::~CPipeServer()
{
    Delete();
}

bool CPipeServer::Create(std::wstring& wstrPipeName)
{
    bool nRet = true;
    std::wstring wstrPipePath(L"\\\\.\\pipe\\");
    wstrPipePath.append(m_strPipeName);

    m_strPipeName = wstrPipePath;


    m_hPipe = CreateNamedPipeW(wstrPipePath.c_str(),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        1024 * 16,
        1024 * 16,
        0,
        NULL);

    
    if (m_hPipe == INVALID_HANDLE_VALUE)
    {
        nRet = false;
    }

    return nRet;
}

bool CPipeServer::Delete()
{
    BOOL bResult = FALSE;

    if (m_hPipe)
    {
        CloseHandle(m_hPipe);
        if (0 != DeleteFileW(m_strPipeName.c_str()))
        {
            // 0이 아닌 경우 삭제에 성공했다.

            m_hPipe = NULL;
            bResult = TRUE;
        }
    }
    return bResult;
}

void CPipeServer::Start()
{
    m_bStop = FALSE;
    char buffer[1024] = { 0, };
    while (true && FALSE == m_bStop) {
        DWORD bytesRead;
        if (ReadFile(m_hPipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead)
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

void CPipeServer::Stop()
{
    m_bStop = TRUE;
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
        DisconnectNamedPipe(m_hPipe);
        ConnectNamedPipe(m_hPipe, NULL);
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