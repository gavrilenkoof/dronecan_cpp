#include "serialcan.h"


namespace slcan
{


static uint8_t nibble2hex(uint8_t x)
{
    // Allocating in RAM because it's faster
    static uint8_t ConversionTable[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
    return ConversionTable[x & 0x0F];
}

static uint8_t hex2nibble(char c)
{
    // Must go into RAM, not flash, because flash is slow
    static uint8_t NumConversionTable[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    static uint8_t AlphaConversionTable[] = {
        10, 11, 12, 13, 14, 15
    };

    uint8_t out = 255;

    if (c >= '0' && c <= '9') {
        out = NumConversionTable[int(c) - int('0')];
    } else if (c >= 'a' && c <= 'f') {
        out = AlphaConversionTable[int(c) - int('a')];
    } else if (c >= 'A' && c <= 'F') {
        out = AlphaConversionTable[int(c) - int('A')];
    }

    if (out == 255) {
//        hex2nibble_error = true;
    }
    return out;
}



Serialcan::Serialcan()
{

}

Serialcan::~Serialcan()
{

}

int Serialcan::setCanBaud(int speed, char *cmd, size_t len)
{
    if(len < 3)
    {
        return 0;
    }

    int idx = 8;
    if(baud2idx.find(speed) != baud2idx.end())
    {
        idx = baud2idx.at(speed);
    }

    return sprintf(cmd, "S%d%c", idx, CARRIAGE_RET);
}

int Serialcan::setEmptyCmd(char *cmd, size_t len)
{
    if(len < 1)
    {
        return 0;
    }

    return sprintf(cmd, "%c", CARRIAGE_RET);
}

int Serialcan::setDisableCanCmd(char *cmd, size_t len)
{

    if(len < 2)
    {
        return 0;
    }

    return sprintf(cmd, "C%c", CARRIAGE_RET);;

}

int Serialcan::setOpenChannel(char *cmd, size_t len)
{

    if(len < 3)
    {
        return 0;
    }

    return sprintf(cmd, "O%c", CARRIAGE_RET);


}

int Serialcan::setClearErrorFlags(char *cmd, size_t len)
{
    if(len < 3)
    {
        return 0;
    }

    return sprintf(cmd, "F%c", CARRIAGE_RET);
}



} // namespace slcan
