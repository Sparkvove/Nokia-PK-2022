#pragma once

#include "BaseState.hpp"

namespace ue {

    class ViewingSingleSmsState : public BaseState {
    public:
        ViewingSingleSmsState(Context &context, int smsListPosition, int notification);

        int notification = 0;

    protected:

        void onAcceptCallbackClicked();

        void onDeclineCallbackClicked();

        void handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber);

        void handleDisconnected() override;

        void handleCallRequest(const common::PhoneNumber callerNumber);
    };
}