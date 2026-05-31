#include "network_operations.h"


void LogHandleResultNetwork(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName) {
    std::ostringstream body;
    body << "\"result\":{"
         << "\"" << fieldName << "\":\"0x" << std::hex << retValue << "\"," 
         << "\"success\":" << ((retValue != 0 && retValue != static_cast<ADDRINT>(-1)) ? "true" : "false")
         << "}";
    Logger::Instance().LogNetworkEvent(api, "after", body.str(), tid);
}

void LogZeroResultNetwork(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName) {
    std::ostringstream body;
    body << "\"result\":{"
         << "\"" << fieldName << "\":\"0x" << std::hex << retValue << "\"," 
         << "\"success\":" << ((retValue == 0) ? "true" : "false")
         << "}";
    Logger::Instance().LogNetworkEvent(api, "after", body.str(), tid);
}

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-send
*/
VOID BeforeSend(THREADID tid, ADDRINT s, ADDRINT buf, ADDRINT len, ADDRINT flags) {

    std::ostringstream body;
    body << "\"args\":{"
         << "\"s\":\"0x" << std::hex << s << "\","
         << "\"buf\":\"0x" << std::hex << buf << "\","
         << "\"len\":\"0x" << std::hex << len << "\","
         << "\"flags\":\"0x" << std::hex << flags << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("send", "before", body.str(), tid);
}

VOID AfterSend(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("send", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-sendto
*/
VOID BeforeSendTo(THREADID tid, ADDRINT s, ADDRINT buf, ADDRINT len, ADDRINT flags, ADDRINT to, ADDRINT tolen) {

    std::ostringstream body;
    body << "\"args\":{"
         << "\"s\":\"0x" << std::hex << s << "\","
         << "\"buf\":\"0x" << std::hex << buf << "\","
         << "\"len\":\"0x" << std::hex << len << "\","
         << "\"flags\":\"0x" << std::hex << flags << "\","
         << "\"to\":\"0x" << std::hex << to << "\","
         << "\"tolen\":\"0x" << std::hex << tolen << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("sendto", "before", body.str(), tid);
}

VOID AfterSendTo(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("sendto", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
*/
VOID BeforeConnect(THREADID tid, ADDRINT s, ADDRINT name, ADDRINT namelen) {

    std::ostringstream body;
    body << "\"args\":{"
         << "\"s\":\"0x" << std::hex << s << "\","
         << "\"name\":\"0x" << std::hex << name << "\","
         << "\"namelen\":\"0x" << std::hex << namelen << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("connect", "before", body.str(), tid);
}

VOID AfterConnect(THREADID tid, ADDRINT retValue) { LogZeroResultNetwork("connect", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-recv
*/
VOID BeforeRecv(THREADID tid, ADDRINT s, ADDRINT buf, ADDRINT len, ADDRINT flags) {

    std::ostringstream body;
    body << "\"args\":{"
         << "\"s\":\"0x" << std::hex << s << "\","
         << "\"buf\":\"0x" << std::hex << buf << "\","
         << "\"len\":\"0x" << std::hex << len << "\","
         << "\"flags\":\"0x" << std::hex << flags << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("recv", "before", body.str(), tid);
}

VOID AfterRecv(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("recv", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-recvfrom
*/
VOID BeforeRecvFrom(THREADID tid, ADDRINT s, ADDRINT buf, ADDRINT len, ADDRINT flags, ADDRINT from, ADDRINT fromlen) {

    std::ostringstream body;
    body << "\"args\":{"
         << "\"s\":\"0x" << std::hex << s << "\","
         << "\"buf\":\"0x" << std::hex << buf << "\","
         << "\"len\":\"0x" << std::hex << len << "\","
         << "\"flags\":\"0x" << std::hex << flags << "\","
         << "\"from\":\"0x" << std::hex << from << "\","
         << "\"fromlen\":\"0x" << std::hex << fromlen << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("recvfrom", "before", body.str(), tid);
}

VOID AfterRecvFrom(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("recvfrom", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
*/
VOID BeforeGetAddrInfo(THREADID tid, ADDRINT pNodeName, ADDRINT pServiceName, ADDRINT pHints, ADDRINT ppResult) {
    std::string pNodeNameValue = ReadAnsiString(reinterpret_cast<const char*>(pNodeName));
    std::string pServiceNameValue = ReadAnsiString(reinterpret_cast<const char*>(pServiceName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"pNodeName\":\"" << Logger::JsonEscape(pNodeNameValue) << "\","
         << "\"pServiceName\":\"" << Logger::JsonEscape(pServiceNameValue) << "\","
         << "\"pHints\":\"0x" << std::hex << pHints << "\","
         << "\"ppResult\":\"0x" << std::hex << ppResult << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("getaddrinfo", "before", body.str(), tid);
}

VOID AfterGetAddrInfo(THREADID tid, ADDRINT retValue) { LogZeroResultNetwork("getaddrinfo", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-gethostbyname
*/
VOID BeforeGetHostByName(THREADID tid, ADDRINT name) {
    std::string nameValue = ReadAnsiString(reinterpret_cast<const char*>(name));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"name\":\"" << Logger::JsonEscape(nameValue) << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("gethostbyname", "before", body.str(), tid);
}

VOID AfterGetHostByName(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("gethostbyname", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfow
*/
VOID BeforeGetAddrInfoW(THREADID tid, ADDRINT pNodeName, ADDRINT pServiceName, ADDRINT pHints, ADDRINT ppResult) {
    std::wstring pNodeNameValue = ReadWideString(reinterpret_cast<const wchar_t*>(pNodeName));
    std::wstring pServiceNameValue = ReadWideString(reinterpret_cast<const wchar_t*>(pServiceName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"pNodeName\":\"" << Logger::JsonEscape(convertWideToStr(pNodeNameValue)) << "\","
         << "\"pServiceName\":\"" << Logger::JsonEscape(convertWideToStr(pServiceNameValue)) << "\","
         << "\"pHints\":\"0x" << std::hex << pHints << "\","
         << "\"ppResult\":\"0x" << std::hex << ppResult << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("GetAddrInfoW", "before", body.str(), tid);
}

VOID AfterGetAddrInfoW(THREADID tid, ADDRINT retValue) { LogZeroResultNetwork("GetAddrInfoW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-httpopenrequesta
*/
VOID BeforeHttpOpenRequestA(THREADID tid, ADDRINT hConnect, ADDRINT lpszVerb, ADDRINT lpszObjectName, ADDRINT lpszVersion, ADDRINT lpszReferrer, ADDRINT lplpszAcceptTypes, ADDRINT dwFlags, ADDRINT dwContext) {
    std::string lpszVerbValue = ReadAnsiString(reinterpret_cast<const char*>(lpszVerb));
    std::string lpszObjectNameValue = ReadAnsiString(reinterpret_cast<const char*>(lpszObjectName));
    std::string lpszVersionValue = ReadAnsiString(reinterpret_cast<const char*>(lpszVersion));
    std::string lpszReferrerValue = ReadAnsiString(reinterpret_cast<const char*>(lpszReferrer));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hConnect\":\"0x" << std::hex << hConnect << "\","
         << "\"lpszVerb\":\"" << Logger::JsonEscape(lpszVerbValue) << "\","
         << "\"lpszObjectName\":\"" << Logger::JsonEscape(lpszObjectNameValue) << "\","
         << "\"lpszVersion\":\"" << Logger::JsonEscape(lpszVersionValue) << "\","
         << "\"lpszReferrer\":\"" << Logger::JsonEscape(lpszReferrerValue) << "\","
         << "\"lplpszAcceptTypes\":\"0x" << std::hex << lplpszAcceptTypes << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"dwContext\":\"0x" << std::hex << dwContext << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("HttpOpenRequestA", "before", body.str(), tid);
}

VOID AfterHttpOpenRequestA(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("HttpOpenRequestA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-httpopenrequestw
*/
VOID BeforeHttpOpenRequestW(THREADID tid, ADDRINT hConnect, ADDRINT lpszVerb, ADDRINT lpszObjectName, ADDRINT lpszVersion, ADDRINT lpszReferrer, ADDRINT lplpszAcceptTypes, ADDRINT dwFlags, ADDRINT dwContext) {
    std::wstring lpszVerbValue = ReadWideString(reinterpret_cast<const wchar_t*>(lpszVerb));
    std::wstring lpszObjectNameValue = ReadWideString(reinterpret_cast<const wchar_t*>(lpszObjectName));
    std::wstring lpszVersionValue = ReadWideString(reinterpret_cast<const wchar_t*>(lpszVersion));
    std::wstring lpszReferrerValue = ReadWideString(reinterpret_cast<const wchar_t*>(lpszReferrer));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hConnect\":\"0x" << std::hex << hConnect << "\","
         << "\"lpszVerb\":\"" << Logger::JsonEscape(convertWideToStr(lpszVerbValue)) << "\","
         << "\"lpszObjectName\":\"" << Logger::JsonEscape(convertWideToStr(lpszObjectNameValue)) << "\","
         << "\"lpszVersion\":\"" << Logger::JsonEscape(convertWideToStr(lpszVersionValue)) << "\","
         << "\"lpszReferrer\":\"" << Logger::JsonEscape(convertWideToStr(lpszReferrerValue)) << "\","
         << "\"lplpszAcceptTypes\":\"0x" << std::hex << lplpszAcceptTypes << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"dwContext\":\"0x" << std::hex << dwContext << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("HttpOpenRequestW", "before", body.str(), tid);
}

VOID AfterHttpOpenRequestW(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("HttpOpenRequestW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-httpsendrequesta
*/
VOID BeforeHttpSendRequestA(THREADID tid, ADDRINT hRequest, ADDRINT lpszHeaders, ADDRINT dwHeadersLength, ADDRINT lpOptional, ADDRINT dwOptionalLength) {
    std::string lpszHeadersValue = ReadAnsiString(reinterpret_cast<const char*>(lpszHeaders));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hRequest\":\"0x" << std::hex << hRequest << "\","
         << "\"lpszHeaders\":\"" << Logger::JsonEscape(lpszHeadersValue) << "\","
         << "\"dwHeadersLength\":\"0x" << std::hex << dwHeadersLength << "\","
         << "\"lpOptional\":\"0x" << std::hex << lpOptional << "\","
         << "\"dwOptionalLength\":\"0x" << std::hex << dwOptionalLength << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("HttpSendRequestA", "before", body.str(), tid);
}

VOID AfterHttpSendRequestA(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("HttpSendRequestA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-httpsendrequestw
*/
VOID BeforeHttpSendRequestW(THREADID tid, ADDRINT hRequest, ADDRINT lpszHeaders, ADDRINT dwHeadersLength, ADDRINT lpOptional, ADDRINT dwOptionalLength) {
    std::wstring lpszHeadersValue = ReadWideString(reinterpret_cast<const wchar_t*>(lpszHeaders));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hRequest\":\"0x" << std::hex << hRequest << "\","
         << "\"lpszHeaders\":\"" << Logger::JsonEscape(convertWideToStr(lpszHeadersValue)) << "\","
         << "\"dwHeadersLength\":\"0x" << std::hex << dwHeadersLength << "\","
         << "\"lpOptional\":\"0x" << std::hex << lpOptional << "\","
         << "\"dwOptionalLength\":\"0x" << std::hex << dwOptionalLength << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("HttpSendRequestW", "before", body.str(), tid);
}

VOID AfterHttpSendRequestW(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("HttpSendRequestW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-httpsendrequestexa
*/
VOID BeforeHttpSendRequestExA(THREADID tid, ADDRINT hRequest, ADDRINT lpBuffersIn, ADDRINT lpBuffersOut, ADDRINT dwFlags, ADDRINT dwContext) {

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hRequest\":\"0x" << std::hex << hRequest << "\","
         << "\"lpBuffersIn\":\"0x" << std::hex << lpBuffersIn << "\","
         << "\"lpBuffersOut\":\"0x" << std::hex << lpBuffersOut << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"dwContext\":\"0x" << std::hex << dwContext << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("HttpSendRequestExA", "before", body.str(), tid);
}

VOID AfterHttpSendRequestExA(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("HttpSendRequestExA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-httpsendrequestexw
*/
VOID BeforeHttpSendRequestExW(THREADID tid, ADDRINT hRequest, ADDRINT lpBuffersIn, ADDRINT lpBuffersOut, ADDRINT dwFlags, ADDRINT dwContext) {

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hRequest\":\"0x" << std::hex << hRequest << "\","
         << "\"lpBuffersIn\":\"0x" << std::hex << lpBuffersIn << "\","
         << "\"lpBuffersOut\":\"0x" << std::hex << lpBuffersOut << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"dwContext\":\"0x" << std::hex << dwContext << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("HttpSendRequestExW", "before", body.str(), tid);
}

VOID AfterHttpSendRequestExW(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("HttpSendRequestExW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-internetopenurla
*/
VOID BeforeInternetOpenUrlA(THREADID tid, ADDRINT hInternet, ADDRINT lpszUrl, ADDRINT lpszHeaders, ADDRINT dwHeadersLength, ADDRINT dwFlags, ADDRINT dwContext) {
    std::string lpszUrlValue = ReadAnsiString(reinterpret_cast<const char*>(lpszUrl));
    std::string lpszHeadersValue = ReadAnsiString(reinterpret_cast<const char*>(lpszHeaders));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hInternet\":\"0x" << std::hex << hInternet << "\","
         << "\"lpszUrl\":\"" << Logger::JsonEscape(lpszUrlValue) << "\","
         << "\"lpszHeaders\":\"" << Logger::JsonEscape(lpszHeadersValue) << "\","
         << "\"dwHeadersLength\":\"0x" << std::hex << dwHeadersLength << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"dwContext\":\"0x" << std::hex << dwContext << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("InternetOpenUrlA", "before", body.str(), tid);
}

VOID AfterInternetOpenUrlA(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("InternetOpenUrlA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-internetopenurlw
*/
VOID BeforeInternetOpenUrlW(THREADID tid, ADDRINT hInternet, ADDRINT lpszUrl, ADDRINT lpszHeaders, ADDRINT dwHeadersLength, ADDRINT dwFlags, ADDRINT dwContext) {
    std::wstring lpszUrlValue = ReadWideString(reinterpret_cast<const wchar_t*>(lpszUrl));
    std::wstring lpszHeadersValue = ReadWideString(reinterpret_cast<const wchar_t*>(lpszHeaders));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hInternet\":\"0x" << std::hex << hInternet << "\","
         << "\"lpszUrl\":\"" << Logger::JsonEscape(convertWideToStr(lpszUrlValue)) << "\","
         << "\"lpszHeaders\":\"" << Logger::JsonEscape(convertWideToStr(lpszHeadersValue)) << "\","
         << "\"dwHeadersLength\":\"0x" << std::hex << dwHeadersLength << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"dwContext\":\"0x" << std::hex << dwContext << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("InternetOpenUrlW", "before", body.str(), tid);
}

VOID AfterInternetOpenUrlW(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("InternetOpenUrlW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winhttp/nf-winhttp-winhttpconnect
*/
VOID BeforeWinHttpConnect(THREADID tid, ADDRINT hSession, ADDRINT pswzServerName, ADDRINT nServerPort, ADDRINT dwReserved) {
    std::wstring pswzServerNameValue = ReadWideString(reinterpret_cast<const wchar_t*>(pswzServerName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hSession\":\"0x" << std::hex << hSession << "\","
         << "\"pswzServerName\":\"" << Logger::JsonEscape(convertWideToStr(pswzServerNameValue)) << "\","
         << "\"nServerPort\":\"0x" << std::hex << nServerPort << "\","
         << "\"dwReserved\":\"0x" << std::hex << dwReserved << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("WinHttpConnect", "before", body.str(), tid);
}

VOID AfterWinHttpConnect(THREADID tid, ADDRINT retValue) { LogHandleResultNetwork("WinHttpConnect", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/windns/nf-windns-dnsquery_a
*/
VOID BeforeDnsQuery_A(THREADID tid, ADDRINT pszName, ADDRINT wType, ADDRINT options, ADDRINT pExtra, ADDRINT ppQueryResults, ADDRINT pReserved) {
    std::string pszNameValue = ReadAnsiString(reinterpret_cast<const char*>(pszName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"pszName\":\"" << Logger::JsonEscape(pszNameValue) << "\","
         << "\"wType\":\"0x" << std::hex << wType << "\","
         << "\"options\":\"0x" << std::hex << options << "\","
         << "\"pExtra\":\"0x" << std::hex << pExtra << "\","
         << "\"ppQueryResults\":\"0x" << std::hex << ppQueryResults << "\","
         << "\"pReserved\":\"0x" << std::hex << pReserved << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("DnsQuery_A", "before", body.str(), tid);
}

VOID AfterDnsQuery_A(THREADID tid, ADDRINT retValue) { LogZeroResultNetwork("DnsQuery_A", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/windns/nf-windns-dnsquery_w
*/
VOID BeforeDnsQuery_W(THREADID tid, ADDRINT pszName, ADDRINT wType, ADDRINT options, ADDRINT pExtra, ADDRINT ppQueryResults, ADDRINT pReserved) {
    std::wstring pszNameValue = ReadWideString(reinterpret_cast<const wchar_t*>(pszName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"pszName\":\"" << Logger::JsonEscape(convertWideToStr(pszNameValue)) << "\","
         << "\"wType\":\"0x" << std::hex << wType << "\","
         << "\"options\":\"0x" << std::hex << options << "\","
         << "\"pExtra\":\"0x" << std::hex << pExtra << "\","
         << "\"ppQueryResults\":\"0x" << std::hex << ppQueryResults << "\","
         << "\"pReserved\":\"0x" << std::hex << pReserved << "\""
         << "}";

    Logger::Instance().LogNetworkEvent("DnsQuery_W", "before", body.str(), tid);
}

VOID AfterDnsQuery_W(THREADID tid, ADDRINT retValue) { LogZeroResultNetwork("DnsQuery_W", retValue, tid, "return"); }

static bool ImageNameContains(IMG img, const char* substr) {
    std::string name = IMG_Name(img);
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    return name.find(substr) != std::string::npos;
}
 
VOID InstrumentNetworkOperations(IMG img, VOID* v) {
 
    if (ImageNameContains(img, "ws2_32")) {
        InstrumentRoutine(img, "send",         AFUNPTR(BeforeSend),         AFUNPTR(AfterSend),         4);
        InstrumentRoutine(img, "sendto",       AFUNPTR(BeforeSendTo),       AFUNPTR(AfterSendTo),       6);
        InstrumentRoutine(img, "connect",      AFUNPTR(BeforeConnect),      AFUNPTR(AfterConnect),      3);
        InstrumentRoutine(img, "recv",         AFUNPTR(BeforeRecv),         AFUNPTR(AfterRecv),         4);
        InstrumentRoutine(img, "recvfrom",     AFUNPTR(BeforeRecvFrom),     AFUNPTR(AfterRecvFrom),     6);
        InstrumentRoutine(img, "getaddrinfo",  AFUNPTR(BeforeGetAddrInfo),  AFUNPTR(AfterGetAddrInfo),  4);
        InstrumentRoutine(img, "gethostbyname",AFUNPTR(BeforeGetHostByName),AFUNPTR(AfterGetHostByName),1);
        InstrumentRoutine(img, "GetAddrInfoW", AFUNPTR(BeforeGetAddrInfoW), AFUNPTR(AfterGetAddrInfoW), 4);
    }
 
    if (ImageNameContains(img, "wininet")) {
        InstrumentRoutine(img, "HttpOpenRequestA",    AFUNPTR(BeforeHttpOpenRequestA),    AFUNPTR(AfterHttpOpenRequestA),    8);
        InstrumentRoutine(img, "HttpOpenRequestW",    AFUNPTR(BeforeHttpOpenRequestW),    AFUNPTR(AfterHttpOpenRequestW),    8);
        InstrumentRoutine(img, "HttpSendRequestA",    AFUNPTR(BeforeHttpSendRequestA),    AFUNPTR(AfterHttpSendRequestA),    5);
        InstrumentRoutine(img, "HttpSendRequestW",    AFUNPTR(BeforeHttpSendRequestW),    AFUNPTR(AfterHttpSendRequestW),    5);
        InstrumentRoutine(img, "HttpSendRequestExA",  AFUNPTR(BeforeHttpSendRequestExA),  AFUNPTR(AfterHttpSendRequestExA),  5);
        InstrumentRoutine(img, "HttpSendRequestExW",  AFUNPTR(BeforeHttpSendRequestExW),  AFUNPTR(AfterHttpSendRequestExW),  5);
        InstrumentRoutine(img, "InternetOpenUrlA",    AFUNPTR(BeforeInternetOpenUrlA),    AFUNPTR(AfterInternetOpenUrlA),    6);
        InstrumentRoutine(img, "InternetOpenUrlW",    AFUNPTR(BeforeInternetOpenUrlW),    AFUNPTR(AfterInternetOpenUrlW),    6);
    }
 
    if (ImageNameContains(img, "winhttp")) {
        InstrumentRoutine(img, "WinHttpConnect", AFUNPTR(BeforeWinHttpConnect), AFUNPTR(AfterWinHttpConnect), 4);
    }
 
    if (ImageNameContains(img, "dnsapi")) {
        InstrumentRoutine(img, "DnsQuery_A", AFUNPTR(BeforeDnsQuery_A), AFUNPTR(AfterDnsQuery_A), 6);
        InstrumentRoutine(img, "DnsQuery_W", AFUNPTR(BeforeDnsQuery_W), AFUNPTR(AfterDnsQuery_W), 6);
    }
}

void StartNetworkOperationsModule() {
    IMG_AddInstrumentFunction(InstrumentNetworkOperations, 0);
}

void FinishNetworkOperationsModule() {
    Logger::Instance().LogMain("Network operations module stopping -> Check NetworkOperations.jsonl for network-specific Windows APIs");
}
