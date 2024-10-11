#ifndef SLCAN_H
#define SLCAN_H


#include <queue>
#include <unordered_map>
#include <array>
#include <inttypes.h>
#include <stdio.h>


#include "framecan.h"



#define print(text) {do{printf(text);fflush(stdout);}while(0);}


namespace slcan
{


class Serialcan
{
public:
    Serialcan();
    virtual ~Serialcan();

public:

    int setCanBaud(int speed, char *cmd, size_t len);
    int setEmptyCmd(char *cmd, size_t len);
    int setDisableCanCmd(char *cmd, size_t len);

private:

    static constexpr char CARRIAGE_RET = '\r';

//    std::queue<Framecan> _q{};

    std::unordered_map<int, int> const baud2idx{
        {1000000, 8},
        {800000, 7},
        {500000, 6},
        {250000, 5},
        {125000, 4},
        {100000, 3},
        {50000, 2},
        {20000, 1},
        {10000, 0}
    };



};


} // namespace slcan


#endif // SLCAN_H
