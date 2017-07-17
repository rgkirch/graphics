#include <fstream>
#include "gtest/gtest.h"

using std::cout;
using std::endl;
using std::string;

TEST(read, openFile) {
    std::ifstream file;
    file.open("/home/richie/Documents/rgkirch/glfw/cinder/assets/small-poloniex-data.json", std::ios_base::in);
    string str;
    file >> str;
//    cout << endl << "str" << str << endl;
}
