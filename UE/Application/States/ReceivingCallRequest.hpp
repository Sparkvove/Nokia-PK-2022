#pragma once

#include "BaseState.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ICallMode.hpp"

namespace ue {

    class ReceivingCallRequest : public BaseState {
    public:
        ReceivingCallRequest(Context &context, const common::PhoneNumber callerNumber, int notification);
        IUeGui::ITextMode &alertMode;
        const common::PhoneNumber callerNumber;
        int notification = 0;

    protected:

        void onAcceptCallbackClicked();

        void onDeclineCallbackClicked();

        void handleCallRequest(const common::PhoneNumber callerNumber);

        void makeDropCall(const common::PhoneNumber callerNumber);

        void handleDropCall(const common::PhoneNumber callerNumber);

        void makeAcceptCall(const common::PhoneNumber callerNumber);

        void handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber) override;

        void handleDisconnected() override;

    };
}
