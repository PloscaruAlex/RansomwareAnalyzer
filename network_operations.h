#pragma once

#include "pin.H"
#include "logger.h"
#include <sstream>
#include <string>
#include "utils.h"

void LogHandleResultNetwork(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName);
void LogZeroResultNetwork(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName);

VOID BeforeSend(THREADID tid, ADDRINT s, ADDRINT buf, ADDRINT len, ADDRINT flags);
VOID AfterSend(THREADID tid, ADDRINT retValue);
VOID BeforeSendTo(THREADID tid, ADDRINT s, ADDRINT buf, ADDRINT len, ADDRINT flags, ADDRINT to, ADDRINT tolen);
VOID AfterSendTo(THREADID tid, ADDRINT retValue);
VOID BeforeConnect(THREADID tid, ADDRINT s, ADDRINT name, ADDRINT namelen);
VOID AfterConnect(THREADID tid, ADDRINT retValue);
VOID BeforeRecv(THREADID tid, ADDRINT s, ADDRINT buf, ADDRINT len, ADDRINT flags);
VOID AfterRecv(THREADID tid, ADDRINT retValue);
VOID BeforeRecvFrom(THREADID tid, ADDRINT s, ADDRINT buf, ADDRINT len, ADDRINT flags, ADDRINT from, ADDRINT fromlen);
VOID AfterRecvFrom(THREADID tid, ADDRINT retValue);

VOID BeforeGetAddrInfo(THREADID tid, ADDRINT pNodeName, ADDRINT pServiceName, ADDRINT pHints, ADDRINT ppResult);
VOID AfterGetAddrInfo(THREADID tid, ADDRINT retValue);
VOID BeforeGetHostByName(THREADID tid, ADDRINT name);
VOID AfterGetHostByName(THREADID tid, ADDRINT retValue);
VOID BeforeGetAddrInfoW(THREADID tid, ADDRINT pNodeName, ADDRINT pServiceName, ADDRINT pHints, ADDRINT ppResult);
VOID AfterGetAddrInfoW(THREADID tid, ADDRINT retValue);
VOID BeforeGetAddrInfoA(THREADID tid, ADDRINT pNodeName, ADDRINT pServiceName, ADDRINT pHints, ADDRINT ppResult);
VOID AfterGetAddrInfoA(THREADID tid, ADDRINT retValue);

VOID BeforeHttpOpenRequestA(THREADID tid, ADDRINT hConnect, ADDRINT lpszVerb, ADDRINT lpszObjectName, ADDRINT lpszVersion, ADDRINT lpszReferrer, ADDRINT lplpszAcceptTypes, ADDRINT dwFlags, ADDRINT dwContext);
VOID AfterHttpOpenRequestA(THREADID tid, ADDRINT retValue);
VOID BeforeHttpOpenRequestW(THREADID tid, ADDRINT hConnect, ADDRINT lpszVerb, ADDRINT lpszObjectName, ADDRINT lpszVersion, ADDRINT lpszReferrer, ADDRINT lplpszAcceptTypes, ADDRINT dwFlags, ADDRINT dwContext);
VOID AfterHttpOpenRequestW(THREADID tid, ADDRINT retValue);
VOID BeforeHttpSendRequestA(THREADID tid, ADDRINT hRequest, ADDRINT lpszHeaders, ADDRINT dwHeadersLength, ADDRINT lpOptional, ADDRINT dwOptionalLength);
VOID AfterHttpSendRequestA(THREADID tid, ADDRINT retValue);
VOID BeforeHttpSendRequestW(THREADID tid, ADDRINT hRequest, ADDRINT lpszHeaders, ADDRINT dwHeadersLength, ADDRINT lpOptional, ADDRINT dwOptionalLength);
VOID AfterHttpSendRequestW(THREADID tid, ADDRINT retValue);
VOID BeforeHttpSendRequestExA(THREADID tid, ADDRINT hRequest, ADDRINT lpBuffersIn, ADDRINT lpBuffersOut, ADDRINT dwFlags, ADDRINT dwContext);
VOID AfterHttpSendRequestExA(THREADID tid, ADDRINT retValue);
VOID BeforeHttpSendRequestExW(THREADID tid, ADDRINT hRequest, ADDRINT lpBuffersIn, ADDRINT lpBuffersOut, ADDRINT dwFlags, ADDRINT dwContext);
VOID AfterHttpSendRequestExW(THREADID tid, ADDRINT retValue);
VOID BeforeInternetOpenUrlA(THREADID tid, ADDRINT hInternet, ADDRINT lpszUrl, ADDRINT lpszHeaders, ADDRINT dwHeadersLength, ADDRINT dwFlags, ADDRINT dwContext);
VOID AfterInternetOpenUrlA(THREADID tid, ADDRINT retValue);
VOID BeforeInternetOpenUrlW(THREADID tid, ADDRINT hInternet, ADDRINT lpszUrl, ADDRINT lpszHeaders, ADDRINT dwHeadersLength, ADDRINT dwFlags, ADDRINT dwContext);
VOID AfterInternetOpenUrlW(THREADID tid, ADDRINT retValue);

VOID BeforeWinHttpConnect(THREADID tid, ADDRINT hSession, ADDRINT pswzServerName, ADDRINT nServerPort, ADDRINT dwReserved);
VOID AfterWinHttpConnect(THREADID tid, ADDRINT retValue);
VOID BeforeDnsQuery_A(THREADID tid, ADDRINT pszName, ADDRINT wType, ADDRINT options, ADDRINT pExtra, ADDRINT ppQueryResults, ADDRINT pReserved);
VOID AfterDnsQuery_A(THREADID tid, ADDRINT retValue);
VOID BeforeDnsQuery_W(THREADID tid, ADDRINT pszName, ADDRINT wType, ADDRINT options, ADDRINT pExtra, ADDRINT ppQueryResults, ADDRINT pReserved);
VOID AfterDnsQuery_W(THREADID tid, ADDRINT retValue);

VOID InstrumentNetworkOperations(IMG img, VOID* v);

void StartNetworkOperationsModule();
void FinishNetworkOperationsModule();
