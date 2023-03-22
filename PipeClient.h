#pragma once

#include <Windows.h>
#include <string>

/** Example Code
#include "IPCAPI.h"
#pragma comment(lib, "WinSysIPCx64.lib")

int main()
{
	CPipeClient* client = nullptr;
	Pipe_API::Create_Client(&client);

	std::wstring pn = L"StartB";
	client->Create(pn, 5000);

	std::string msg("aaaab");
	DWORD dwWritten = 0;
	client->Write((LPVOID)msg.c_str(), msg.size(), &dwWritten);

	return 0;
}

 */

/**
* @class CPipeClient
* @brief 윈도우 OS에서 파이프 통신하는 클래스
*/
class CPipeClient
{
public:
    /**
    * @brief 생성자
    */
    CPipeClient();

    /**
    * @brief 소멸자
    */
    virtual ~CPipeClient();

    /**
    * @brief 파이프 생성
    * @param[in] wstrPipeName 생성할 파이프 이름
    * @param[in] dwTimeOut 파이프 생성 타임아웃(ms)
    * @return 성공시 true, 실패시 false 반환
    */
    virtual bool Create(std::wstring & wstrPipeName, DWORD dwTimeOut);

    /**
    * @brief 파이프에 데이터 쓰기
    * @param[in] lpBuffer 쓸 데이터
    * @param[in] dwBufferSize 데이터 크기
    * @param[out] lpBytesWritten 실제로 쓴 데이터 크기
    * @return 성공시 true, 실패시 false 반환
    */
    virtual bool Write(LPVOID lpBuffer, DWORD dwBufferSize, LPDWORD lpBytesWritten);

private:
    HANDLE m_hPipe; ///< 파이프 핸들
};
