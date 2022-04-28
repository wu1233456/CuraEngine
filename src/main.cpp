//Copyright (c) 2018 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.

#include <iostream> //To change the formatting of std::cerr.
#include <signal.h> //For floating point exceptions.
#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
    #include <sys/resource.h> //For setpriority.
#endif
#include "Application.h"
#include "utils/logoutput.h"

namespace cura
{

//Signal handler for a "floating point exception", which can also be integer division by zero errors.
void signal_FPE(int n)
{
    (void)n;
    logError("Arithmetic exception.\n");
    exit(1);
}

}//namespace cura

int main(int argc, char **argv)
{//"-v","-j","C:/Users/Croquis/Desktop/fdmextruder.def.json"***,"-v","-j","C:/Users/Croquis/Desktop/fdmprinter.def.json","-v","-j","C:/Users/Croquis/Desktop/fdmextruder1.def.json","-e1"

    const char* myargv[20] = {"a","slice","-v","-j","C:/Users/Croquis/Desktop/fdmprinter.def(1).json","-v","-j","C:/Users/Croquis/Desktop/fdmextruder.def.json","-e0","-v","-j","C:/Users/Croquis/Desktop/fdmprinter.def.json","-v","-j","C:/Users/Croquis/Desktop/fdmextruder1.def.json","-e1","-o","D:/g_code/40mm.gcode","-l","C:/Users/Croquis/Documents/sw_2018/40mm.STL" };
    int myargc = 20;
#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))


    //Lower the process priority on linux and mac. On windows this is done on process creation from the GUI.
    setpriority(PRIO_PROCESS, 0, 10);
#endif

#ifndef DEBUG
    //Register the exception handling for arithmetic exceptions, this prevents the "something went wrong" dialog on windows to pop up on a division by zero.
    signal(SIGFPE, cura::signal_FPE);
#endif
    std::cerr << std::boolalpha;

    cura::Application::getInstance().run(myargc, (char**)myargv);

    return 0;
}
