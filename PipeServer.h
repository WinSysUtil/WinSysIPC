#pragma once
#include <Windows.h>
#include <string>
#include <functional>
#pragma hdrstop

/** :: Example Code 
int main() {
    std::wstring wstrPipeName(L"myfifo");
    Server server(wstrPipeName);
    server.SetMessageReceivedCallback(std::bind(&OnServerMessageReceived, std::placeholders::_1));
    server.Start();
    return 0;
}
 */

/**
 * \brief Named Pipe Server 클래스.
 */
class CPipeServer {
public:
    /**
     * \brief Named Pipe Server 생성자.
     * \param wstrPipeName Named Pipe 이름.
     */
    CPipeServer(std::wstring& wstrPipeName);

    /**
     * \brief Server 시작.
     */
    void Start();

    /**
     * \brief Message Received Callback 등록.
     * \param callback 등록할 콜백 함수.
     */
    void SetMessageReceivedCallback(const std::function<void(const std::string&)>& callback);

    /**
     * \brief 에러 핸들러.
     */
    void ErrorHandler();

private:
    HANDLE m_pipe; ///< Named Pipe 핸들.
    std::function<void(const std::string&)> m_messageReceivedCallback; ///< Message Received Callback.

    /**
     * \brief Message Received Callback.
     * \param message 받은 메시지.
     */
    void MessageReceivedCallback(const std::string& message);
};
