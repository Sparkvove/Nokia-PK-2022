#include "ConnectedState.hpp"
#include "ReceivingCallRequest.hpp"
#include "SendingCallRequest.hpp"
#include "TalkingState.hpp"
#include "UeGui/ICallMode.hpp"
#include "NotConnectedState.hpp"


namespace ue {

    TalkingState::TalkingState(Context &context, const common::PhoneNumber phoneNumber, int notification)
            : BaseState(context, "TalkingState"),  talkingMode(context.user.talkingMode()), phoneNumber(phoneNumber)  {
        context.user.acceptCallback([this] { onAcceptCallbackClicked(); });
        context.user.rejectCallback([this] { onDeclineCallbackClicked(); });
        this->notification = notification;
    }

    void TalkingState::onAcceptCallbackClicked() {
        talk();
    }

    void TalkingState::onDeclineCallbackClicked() {
        makeDropCall(phoneNumber);
    }

    void TalkingState::talk() {
        common::PhoneNumber receiverNumber = this->phoneNumber;
        std::string talkText = talkingMode.getOutgoingText();
        context.logger.logInfo(talkText);
        context.logger.logInfo(receiverNumber);
        context.bts.talk(receiverNumber, talkText);
        talkingMode.clearOutgoingText();
        talkingMode.appendIncomingText("to " +common::to_string(receiverNumber) +": " + talkText);
    }

    void TalkingState::handleTalkMessage(const std::string talkText,const common::PhoneNumber senderNumber) {
        talkingMode.appendIncomingText("from "+common::to_string(senderNumber)+": "+talkText);
    }

    void TalkingState::makeDropCall(const common::PhoneNumber callerNumber) {
        context.bts.declineCall(callerNumber);
        context.logger.logInfo("Dropping call from " + common::to_string(callerNumber));
        talkingMode.clearIncomingText();
        talkingMode.appendIncomingText("Incoming text");
        context.setState<ConnectedState>(notification);
    }

    void TalkingState::handleDropCall(const common::PhoneNumber callerNumber) {
        talkingMode.clearIncomingText();
        talkingMode.appendIncomingText("Incoming text");
        context.setState<ConnectedState>(notification);
    }

    void TalkingState::handleDisconnected() {
        context.setState<NotConnectedState>();
    }

    void TalkingState::handleSMSReceive(const std::string smsText, const common::PhoneNumber senderNumber) {
        this->notification = 1;
        SMS sms1 = SMS(smsText, senderNumber, "received");
        SMS_DB ourDataBase = context.user.getSmsDB();
        ourDataBase.addSmsToDB(sms1);
        context.user.setSmsDB(ourDataBase);
    }

    void TalkingState::handleCallRequest(const common::PhoneNumber callerNumber) {
        context.bts.declineCall(callerNumber);
    }
}
