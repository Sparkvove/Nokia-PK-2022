#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;

};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (int), (final));
    MOCK_METHOD(int, getMenuIndex, (), (final));
    MOCK_METHOD(void, showViewingSms, (), (final));
    MOCK_METHOD(SMS, returnSingleSms, (int), (final));
    MOCK_METHOD(void, showSingleSms, (int), (final));
    MOCK_METHOD(IUeGui::ISmsComposeMode& , composeSmsMode, (), (final));
    MOCK_METHOD(IUeGui::IDialMode& , dialComposeMode, (), (final));
    MOCK_METHOD(IUeGui::ICallMode& , talkingMode, (), (final));
    MOCK_METHOD(IUeGui::ITextMode& , callFromMode, (const common::PhoneNumber callerNumber), (final));
    MOCK_METHOD(IUeGui::ITextMode& , callToMode, (const common::PhoneNumber receiverNumber), (final));
    MOCK_METHOD(void , acceptCallback, (IUeGui::Callback acceptCallback), (final));
    MOCK_METHOD(void , rejectCallback, (IUeGui::Callback rejectCallback), (final));
    MOCK_METHOD(SMS_DB& , getSmsDB, (), (final));
    MOCK_METHOD(void , setSmsDB, (SMS_DB &smsDb), (final));
};

}
