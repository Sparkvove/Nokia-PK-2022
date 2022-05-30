#include "ConnectedState.hpp"
#include "SendingCallRequest.hpp"
#include "TalkingState.hpp"
#include "NotConnectedState.hpp"

namespace ue {

    SendingCallRequestState::SendingCallRequestState(Context &context, int notification): BaseState(context, "SendingCallRequestState"),
    dialMode(context.user.dialComposeMode()) {
        context.user.acceptCallback([this] { onAcceptCallbackClicked(); });
        context.user.rejectCallback([this] { onDeclineCallbackClicked(); });
        this->notification = notification;
    }

    void SendingCallRequestState::onAcceptCallbackClicked() {
        makeCall();
    }

    void SendingCallRequestState::onDeclineCallbackClicked() {
        common::PhoneNumber receiverNumber = dialMode.getPhoneNumber();
        makeDropCall(receiverNumber);
    }

    void SendingCallRequestState::makeCall() {
        common::PhoneNumber receiverNumber = dialMode.getPhoneNumber();
        context.logger.logInfo("Calling to "+ common::to_string(receiverNumber));
        context.bts.makeCall(receiverNumber);
        context.user.callToMode(receiverNumber);
    }

    void SendingCallRequestState::handleDropCall(const common::PhoneNumber callerNumber) {
        context.setState<ConnectedState>(notification);
    }

    void SendingCallRequestState::makeDropCall(const common::PhoneNumber callerNumber) {
        context.bts.declineCall(callerNumber);
        context.logger.logInfo("Dropping call from "+ common::to_string(callerNumber));
        context.setState<ConnectedState>(notification);
    }

    void SendingCallRequestState::handleAcceptCall(const common::PhoneNumber callerNumber) {
        context.setState<TalkingState>(callerNumber,notification);
    }

    void SendingCallRequestState::handleDisconnected() {
        context.setState<NotConnectedState>();
    }

    void SendingCallRequestState::handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber) {
        this->notification = 1;
        SMS sms1 = SMS(smsText, senderNumber, "received");
        SMS_DB ourDataBase = context.user.getSmsDB();
        ourDataBase.addSmsToDB(sms1);
        context.user.setSmsDB(ourDataBase);
    }

    void SendingCallRequestState::handleCallRequest(const common::PhoneNumber callerNumber) {
        context.bts.declineCall(callerNumber);
    }

}
