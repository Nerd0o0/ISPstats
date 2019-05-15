#include <iostream>
#include "include/Server.h"
#include "src/DBConnector.cpp"
#include <string.h>
#include <stdlib.h>
#include <exception>

/*int main(int i,char* args[]) {
    DBConnector conn;
    conn.getSprints();
    std::cout << "Вывод" << std::endl;
    return 0;
    //Server app;
    //return app.run(i,args);
}*/
POCO_SERVER_MAIN(Server)