#include "ConnectedState.hpp"
#include "ReceivingCallRequest.hpp"
#include "TalkingState.hpp"
#include "NotConnectedState.hpp"

namespace ue {

    ReceivingCallRequest::ReceivingCallRequest(Context &context,const common::PhoneNumber callerNumber, int notification)
            : BaseState(context, "ReceivingCallRequest"), alertMode(context.user.callFromMode(callerNumber)),
              callerNumber(callerNumber) {
        context.user.acceptCallback([this] { onAcceptCallbackClicked(); });
        context.user.rejectCallback([this] { onDeclineCallbackClicked(); });
        this->notification = notification;
    }

    void ReceivingCallRequest::onAcceptCallbackClicked(){

        makeAcceptCall(callerNumber);
    }

    void ReceivingCallRequest::onDeclineCallbackClicked()
    {
        makeDropCall(callerNumber);
    }

    void ReceivingCallRequest::handleCallRequest(const common::PhoneNumber callerNumber) {
        context.bts.declineCall(callerNumber);
    }

    void ReceivingCallRequest::makeDropCall(const common::PhoneNumber callerNumber) {
        context.bts.declineCall(callerNumber);
        context.logger.logInfo("Dropping call from " + common::to_string(callerNumber));
        context.setState<ConnectedState>(notification);
    }

    void ReceivingCallRequest::handleDropCall(const common::PhoneNumber callerNumber) {
        context.setState<ConnectedState>(notification);
    }

    void ReceivingCallRequest::makeAcceptCall(const common::PhoneNumber callerNumber) {
        context.bts.acceptCall(callerNumber);
        context.logger.logInfo("Accepting call from " + common::to_string(callerNumber));
        context.setState<TalkingState>(callerNumber,notification);
    }

    void ReceivingCallRequest::handleDisconnected() {
        context.setState<NotConnectedState>();
    }

    void ReceivingCallRequest::handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber) {
        this->notification = 1;
        SMS sms1 = SMS(smsText, senderNumber, "received");
        SMS_DB ourDataBase = context.user.getSmsDB();
        ourDataBase.addSmsToDB(sms1);
        context.user.setSmsDB(ourDataBase);
    }


}
