#include <iostream>
#include <stdlib.h>
#include <libconfig.h++>


int main()
{

    libconfig::Config config;

    try
    {
        config.readFile("config.cfg");
    } 
    catch (libconfig::FileIOException &e)
    {
        std::cerr << "FileIOException occurred. Could not read \"example.cfg\"!!\n";
        exit (EXIT_FAILURE);
    } 
    catch (libconfig::ParseException &e)
    {

        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine() << " - " << e.getError() << std::endl;
        return(EXIT_FAILURE);
    }

    std::string str = config.lookup("master.TargetNBD");
    int s = config.lookup("master.SlaveSize");
    std::cout << str << std::endl;
    std::cout << s << std::endl;

    return 0;
}