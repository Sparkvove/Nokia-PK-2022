#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/SMSDBMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include <memory>

namespace ue {
    using namespace ::testing;

    class ApplicationTestSuite : public Test {
    protected:
        const common::PhoneNumber PHONE_NUMBER{112};
        const common::PhoneNumber PHONE_NUMBER2{113};
        const common::BtsId BTS_ID{42};
        const std::string MESSAGE = "Hello World";
        NiceMock<common::ILoggerMock> loggerMock;
        StrictMock<IBtsPortMock> btsPortMock;
        NiceMock<IUserPortMock> userPortMock;
        NiceMock<SMSDBMock> smsDbMock;
        StrictMock<ITimerPortMock> timerPortMock;

        Expectation expectNotConnected = EXPECT_CALL(userPortMock, showNotConnected());

        Application objectUnderTest{PHONE_NUMBER,
                                    loggerMock,
                                    btsPortMock,
                                    userPortMock,
                                    timerPortMock};
    };

    struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
    {
        void requestAttachOnSib();
    };

    void ApplicationNotConnectedTestSuite::requestAttachOnSib()
    {
        EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
        EXPECT_CALL(timerPortMock, startTimer(_));
        EXPECT_CALL(userPortMock, showConnecting());
        objectUnderTest.handleSib(BTS_ID);
    }

    TEST_F(ApplicationNotConnectedTestSuite, shallRequestAttachOnSib)
    {
        requestAttachOnSib();
    }

    struct ApplicationConnectingTestSuite : ApplicationNotConnectedTestSuite
    {
        ApplicationConnectingTestSuite();
    };

    ApplicationConnectingTestSuite::ApplicationConnectingTestSuite()
    {
        requestAttachOnSib();
    }

    TEST_F(ApplicationConnectingTestSuite, shallCompleteAttachWhenAttachAccepted)
    {
        EXPECT_CALL(timerPortMock, stopTimer());
        EXPECT_CALL(userPortMock, showConnected(0));
        objectUnderTest.handleAttachAccept();
    }

    TEST_F(ApplicationConnectingTestSuite, shallFailAttachWhenAttachRejected)
    {
        EXPECT_CALL(timerPortMock, stopTimer());
        EXPECT_CALL(userPortMock, showNotConnected());
        objectUnderTest.handleAttachReject();
    }

    TEST_F(ApplicationConnectingTestSuite, shallFailAttachWhenAttachTimeout)
    {
        EXPECT_CALL(userPortMock, showNotConnected());
        objectUnderTest.handleTimeout();
    }

    struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite
    {
        ApplicationConnectedTestSuite();
    };

    ApplicationConnectedTestSuite::ApplicationConnectedTestSuite()
    {
        EXPECT_CALL(timerPortMock, stopTimer());
        EXPECT_CALL(userPortMock, showConnected(0));
        objectUnderTest.handleAttachAccept();
    }

    TEST_F(ApplicationConnectedTestSuite, shallHandleDisconnect)
    {
        EXPECT_CALL(userPortMock, showNotConnected());
        objectUnderTest.handleDisconnected();
    }
}