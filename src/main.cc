

#include "dronecanapp.h"
//#include "dronecansetup.h"
//#include "Core/dronecancore.h"


int main(int argc, char *argv[])
{

    qSetMessagePattern("%{type} (%{file}:%{line}): %{message}\n");

    DronecanApp app(argc, argv);
    app.init();


    auto exec_2 = app.execSetup();

//    app.execApp();

    return exec_2;

}

