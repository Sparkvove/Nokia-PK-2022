#pragma once

#include "BaseState.hpp"

namespace ue {

    class TalkingState : public BaseState {
    public:
        TalkingState(Context &context,const common::PhoneNumber phoneNumber, int notification);
        IUeGui::ICallMode &talkingMode;
        const common::PhoneNumber phoneNumber;
        int notification = 0;

    protected:

        void onAcceptCallbackClicked();

        void onDeclineCallbackClicked();

        void talk();

        void handleTalkMessage(const std::string talkText, const common::PhoneNumber senderNumber);

        void handleDropCall(const common::PhoneNumber callerNumber);

        void makeDropCall(const common::PhoneNumber callerNumber);

        void handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber) override;

        void handleCallRequest(const common::PhoneNumber callerNumber);

        void handleDisconnected() override;
    };
}