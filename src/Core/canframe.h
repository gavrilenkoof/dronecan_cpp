#ifndef CANFRAME_H
#define CANFRAME_H

#include <cstdint>
#include <cstring>


struct CANFrame
{
    static const uint32_t MaskStdID = 0x000007FFU;
    static const uint32_t MaskExtID = 0x1FFFFFFFU;
    static const uint32_t FlagEFF = 1U << 31;                  ///< Extended frame format
    static const uint32_t FlagRTR = 1U << 30;                  ///< Remote transmission request
    static const uint32_t FlagERR = 1U << 29;                  ///< Error frame

#if HAL_CANFD_SUPPORTED
    static const uint8_t NonFDCANMaxDataLen = 8;
    static const uint8_t MaxDataLen = 64;
#else
    static const uint8_t NonFDCANMaxDataLen = 8;
    static const uint8_t MaxDataLen = 8;
#endif
    uint32_t id;                ///< CAN ID with flags (above)
    union {
        uint8_t data[MaxDataLen];
        uint32_t data_32[MaxDataLen/4];
    };
    uint8_t dlc;                ///< Data Length Code
    bool canfd;

    CANFrame() :
        id(0),
        dlc(0),
        canfd(false)
    {
        memset(data,0, MaxDataLen);
    }

    CANFrame(uint32_t can_id, const uint8_t* can_data, uint8_t data_len, bool canfd_frame = false);

    bool operator!=(const CANFrame& rhs) const
    {
        return !operator==(rhs);
    }
    bool operator==(const CANFrame& rhs) const
    {
        return (id == rhs.id) && (dlc == rhs.dlc) && (memcmp(data, rhs.data, dlc) == 0);
    }

    // signed version of id, for use by scriping where uint32_t is expensive
    int32_t id_signed(void) const {
        return isExtended()? int32_t(id & MaskExtID) : int32_t(id & MaskStdID);
    }

    bool isExtended()                  const
    {
        return id & FlagEFF;
    }
    bool isRemoteTransmissionRequest() const
    {
        return id & FlagRTR;
    }
    bool isErrorFrame()                const
    {
        return id & FlagERR;
    }
    void setCanFD(bool canfd_frame)
    {
        canfd = canfd_frame;
    }

    bool isCanFDFrame() const
    {
        return canfd;
    }

    static uint8_t dlcToDataLength(uint8_t dlc)
    {
        /*
        Data Length Code      9  10  11  12  13  14  15
        Number of data bytes 12  16  20  24  32  48  64
        */
        if (dlc <= 8) {
            return dlc;
        } else if (dlc == 9) {
            return 12;
        } else if (dlc == 10) {
            return 16;
        } else if (dlc == 11) {
            return 20;
        } else if (dlc == 12) {
            return 24;
        } else if (dlc == 13) {
            return 32;
        } else if (dlc == 14) {
            return 48;
        }
        return 64;
    };

    static uint8_t dataLengthToDlc(uint8_t data_length)
    {
        if (data_length <= 8) {
            return data_length;
        } else if (data_length <= 12) {
            return 9;
        } else if (data_length <= 16) {
            return 10;
        } else if (data_length <= 20) {
            return 11;
        } else if (data_length <= 24) {
            return 12;
        } else if (data_length <= 32) {
            return 13;
        } else if (data_length <= 48) {
            return 14;
        }
        return 15;
    };
    /**
     * CAN frame arbitration rules, particularly STD vs EXT:
     *     Marco Di Natale - "Understanding and using the Controller Area Network"
     *     http://www6.in.tum.de/pub/Main/TeachingWs2013MSE/CANbus.pdf
     */
    bool priorityHigherThan(const CANFrame& rhs) const;
    bool priorityLowerThan(const CANFrame& rhs) const
    {
        return rhs.priorityHigherThan(*this);
    }
};


#endif // CANFRAME_H
