#include "PipeClient.h"

/**
* @brief 생성자
*/
CPipeClient::CPipeClient()
{
    m_hPipe = INVALID_HANDLE_VALUE;
}

/**
* @brief 소멸자
*/
CPipeClient::~CPipeClient()
{
    CloseHandle(m_hPipe);
}

/**
* @brief 파이프 생성
* @param[in] lpszPipeName 생성할 파이프 이름
* @param[in] dwTimeOut 파이프 생성 타임아웃(ms)
* @return 성공시 true, 실패시 false 반환
*/
bool CPipeClient::Create(std::wstring& wstrPipeName, DWORD dwTimeOut)
{
    bool nRet = true;
    std::wstring wstrPipePath(L"\\\\.\\pipe\\");
    wstrPipePath.append(wstrPipeName);

    while (true) {
        m_hPipe = CreateFile(
            wstrPipePath.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (m_hPipe == INVALID_HANDLE_VALUE) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_PIPE_BUSY) {
                if (!WaitNamedPipe(wstrPipePath.c_str(), dwTimeOut)) {
                    // 대기 시간이 지난 경우
                    nRet = false;
                    break;
                }
            }
            else {
                // 다른 오류가 발생한 경우
                nRet = false;
                break;
            }
        }
        else {
            break;
        }
    }

    return nRet;
}


/**
* @brief 파이프에 데이터 쓰기
* @param[in] lpBuffer 쓸 데이터
* @param[in] dwBufferSize 데이터 크기
* @param[out] lpBytesWritten 실제로 쓴 데이터 크기
* @return 성공시 true, 실패시 false 반환
*/
bool CPipeClient::Write(LPVOID lpBuffer, DWORD dwBufferSize, LPDWORD lpBytesWritten)
{
    if (m_hPipe == INVALID_HANDLE_VALUE) {
        return false;
    }

    if (!WriteFile(m_hPipe, lpBuffer, dwBufferSize, lpBytesWritten, NULL)) {
        return false;
    }

    return true;
}
