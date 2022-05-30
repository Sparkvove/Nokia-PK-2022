#pragma once

#include "BaseState.hpp"
#include "ConnectedState.hpp"
#include "UeGui/IDialMode.hpp"

namespace ue {

    class SendingCallRequestState : public BaseState {
    public:
        SendingCallRequestState(Context &context, int notification);
        IUeGui::IDialMode &dialMode;
        int notification = 0;

    protected:

        void onAcceptCallbackClicked();

        void onDeclineCallbackClicked();

        void makeCall();

        void handleDropCall(const common::PhoneNumber callerNumber);

        void handleAcceptCall(const common::PhoneNumber callerNumber);

        void makeDropCall(const common::PhoneNumber callerNumber);

        void handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber) override;

        void handleDisconnected() override;

        void handleCallRequest(const common::PhoneNumber callerNumber);
    };
}
