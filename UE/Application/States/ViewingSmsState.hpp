#pragma once

#include "BaseState.hpp"

namespace ue {

    class ViewingSmsState : public BaseState {
    public:
        ViewingSmsState(Context &context, int notification);

        int notification = 0;

    protected:

        void onAcceptCallbackClicked();

        void onDeclineCallbackClicked();

        void handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber);

        void handleDisconnected() override;

        void handleCallRequest(const common::PhoneNumber callerNumber);
    };
}