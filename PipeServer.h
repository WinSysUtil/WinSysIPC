#pragma once
#include <Windows.h>
#include <string>
#include <functional>
#pragma hdrstop

/** :: Example Code 
* 

void OnServerMessageReceived(const std::string& message) {
	std::cout << "Received message from server: " << message << std::endl;
}
int main() {
    std::wstring wstrPipeName(L"myfifo");
    Server server;
    server.Create(wstrPipeName);
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
     */
    CPipeServer();

    /**
     * 파이프를 생성한다..
     * 
     * \param wstrPipeName Named Pipe 이름.
     * \return 
     */
    virtual bool Create(std::wstring& wstrPipeName);

    /**
     * \brief Server 시작.
     */
    virtual void Start();

    /**
     * \brief Message Received Callback 등록.
     * \param callback 등록할 콜백 함수.
     */
    virtual void SetMessageReceivedCallback(const std::function<void(const std::string&)>& callback);

    /**
     * \brief 에러 핸들러.
     */
    virtual void ErrorHandler();

private:
    HANDLE m_pipe; ///< Named Pipe 핸들.
    std::function<void(const std::string&)> m_messageReceivedCallback; ///< Message Received Callback.

    /**
     * \brief Message Received Callback.
     * \param message 받은 메시지.
     */
    virtual void MessageReceivedCallback(const std::string& message);
};
