#include "ConnectedState.hpp"
#include "ViewingSmsState.hpp"
#include "ViewingSingleSmsState.hpp"
#include "NotConnectedState.hpp"
#include "ReceivingCallRequest.hpp"

namespace ue {

    ViewingSmsState::ViewingSmsState(Context &context, int notification)
            : BaseState(context, "ViewingSmsState") {
        context.user.acceptCallback([this] { onAcceptCallbackClicked(); });
        context.user.rejectCallback([this] { onDeclineCallbackClicked(); });
        context.user.showViewingSms();
        this->notification = notification;
    }

    void ViewingSmsState::onAcceptCallbackClicked() {
        int currentMenuIndex = context.user.getMenuIndex();
        context.setState<ViewingSingleSmsState>(currentMenuIndex + 1, notification);
    }

    void ViewingSmsState::onDeclineCallbackClicked() {
        context.setState<ConnectedState>(notification);
    }

    void ViewingSmsState::handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber) {
        SMS sms = SMS(smsText, senderNumber, "received");
        SMS_DB ourDataBase = context.user.getSmsDB();
        ourDataBase.addSmsToDB(sms);
        context.user.setSmsDB(ourDataBase);
        context.user.showViewingSms();
    }

    void ViewingSmsState::handleDisconnected() {
        context.setState<NotConnectedState>();
    }

    void ViewingSmsState::handleCallRequest(const common::PhoneNumber callerNumber) {
        context.setState<ReceivingCallRequest>(callerNumber, notification);
    }
}