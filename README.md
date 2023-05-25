# WinSysIPC
윈도우 시스템에서 사용되는 IPC통신을 편리하게 제공해주는 라이브러리


# 예제 코드

## 파이프 서버 생성
```cpp
   m_pPipeThread = std::make_unique<std::thread>([&]()
        {
           if (nullptr == m_pServer)
                Pipe_API::Create_Server(&m_pServer);
            std::wstring strPipeName = STR_FLEXI_SERVICE_PIPE_NAME;
            if (false == m_pServer->Create(strPipeName))
            {
                WCHAR szDbgMsg[1024] = { 0, };
                swprintf_s(szDbgMsg, _countof(szDbgMsg), L"Pipe Create Failed ! Error Code [0x%X]", GetLastError());
                OutputDebugString(szDbgMsg);
            }
            else
            {
                OutputDebugString(L">>>>> SERVER PIPE CREATE SUCCESS !");
            }
            m_pServer->SetMessageReceivedCallback(PipeServerCallback);
            m_pServer->Start();
        }
    );
```

## 파이프 클라이언트 생성
```cpp
	CPipeClient* client = nullptr;
	Pipe_API::Create_Client(&client);

	std::wstring pn = L"StartB";
	client->Create(pn, 5000);

	std::string msg("aaaab");
	DWORD dwWritten = 0;
	client->Write((LPVOID)msg.c_str(), msg.size(), &dwWritten);
```
