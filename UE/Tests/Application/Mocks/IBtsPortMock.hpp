#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleDisconnected, (), (final));
    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    MOCK_METHOD(void, handleSMSReceive, (const std::string smsText, const common::PhoneNumber senderNumber), (final));
    MOCK_METHOD(void, handleCallRequest, (const common::PhoneNumber callerNumber), (final));
    MOCK_METHOD(void, handleDropCall, (const common::PhoneNumber callerNumber), (final));
    MOCK_METHOD(void, handleAcceptCall, (const common::PhoneNumber callerNumber), (final));
    MOCK_METHOD(void, makeDropCall, (const common::PhoneNumber callerNumber), (final));
    MOCK_METHOD(void, makeAcceptCall, (const common::PhoneNumber callerNumber), (final));
    MOCK_METHOD(void, handleTalkMessage, (const std::string talkText, const common::PhoneNumber senderNumber), (final));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendSms, (common::PhoneNumber, std::string), (final));
    MOCK_METHOD(void, makeCall, (common::PhoneNumber), (final));
    MOCK_METHOD(void, declineCall, (common::PhoneNumber), (final));
    MOCK_METHOD(void, acceptCall, (common::PhoneNumber), (final));
    MOCK_METHOD(void, talk, (common::PhoneNumber, std::string), (final));
};

}
