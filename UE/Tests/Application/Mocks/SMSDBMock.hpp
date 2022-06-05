#pragma once

#include <gmock/gmock.h>
#include "SMS/SMS_DB.hpp"
#include "SMS/SMS.hpp"

namespace ue
{
    class SMSDBMock : public SMS_DB
    {
    public:
        SMSDBMock();
        ~SMSDBMock();

        MOCK_METHOD(void, addSmsToDB, (SMS sms));
        MOCK_METHOD(SMS, getSingleSmsAt, (int smsListPosition));
        MOCK_METHOD(std::vector<SMS>, getAllSMS, ());
    };

}
