

#include "dronecanapp.h"
//#include "dronecansetup.h"
//#include "Core/dronecancore.h"


int main(int argc, char *argv[])
{

    DronecanApp app(argc, argv);


    app.init();


    app.execSetup();

    auto exec_2 = app.execApp();

    return exec_2;

}

