#include "application.h"
#include <iostream>
#include <string.h>
using namespace std;
int main(int argc, char *argv[])
{
    cout<<SCR_DIR<<std::endl;
    Application app;
    app.Run();
}
