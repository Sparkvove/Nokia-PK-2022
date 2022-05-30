#include "ConnectedState.hpp"
#include "ViewingSmsState.hpp"
#include "ViewingSingleSmsState.hpp"
#include "NotConnectedState.hpp"
#include "ReceivingCallRequest.hpp"

namespace ue {

    ViewingSingleSmsState::ViewingSingleSmsState(Context &context, int smsListPosition, int notification)
            : BaseState(context, "ViewingSingleSmsState") {
        context.user.acceptCallback([this] { onAcceptCallbackClicked(); });
        context.user.rejectCallback([this] { onDeclineCallbackClicked(); });
        context.user.showSingleSms(smsListPosition);
        this->notification = notification;
    }

    void ViewingSingleSmsState::onAcceptCallbackClicked() {}

    void ViewingSingleSmsState::onDeclineCallbackClicked() {
        context.setState<ViewingSmsState>(notification);
    }

    void ViewingSingleSmsState::handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber) {
        SMS sms1 = SMS(smsText, senderNumber, "received");
        SMS_DB ourDataBase = context.user.getSmsDB();
        ourDataBase.addSmsToDB(sms1);
        context.user.setSmsDB(ourDataBase);
    }

    void ViewingSingleSmsState::handleDisconnected() {
        context.setState<NotConnectedState>();
    }

    void ViewingSingleSmsState::handleCallRequest(const common::PhoneNumber callerNumber) {
        context.setState<ReceivingCallRequest>(callerNumber, notification);
    }
}