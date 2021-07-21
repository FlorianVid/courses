#include <window.h>


#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include<iostream>
using namespace std;

std::string get_current_dir() {
   char buff[FILENAME_MAX]; //create string buffer to hold path
   GetCurrentDir( buff, FILENAME_MAX );
   string current_working_dir(buff);
   return current_working_dir;
}

int main(int argc, char **argv) {

cout << get_current_dir() << endl;
QApplication app (argc, argv);

Window window;

window.show();



return app.exec();

}


