#pragma once

#define CHECK_STATUS(status, errorMessage)                                              \
{                                                                                       \
    if (!status)                                                                        \
    {                                                                                   \
        if (errorMessage)                                                               \
        {                                                                               \
            MGlobal::displayError(MString(errorMessage) + status.errorString());        \
        }                                                                               \
        return status;                                                                  \
    }                                                                                   \
}