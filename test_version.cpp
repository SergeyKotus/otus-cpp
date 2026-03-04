#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <boost/test/unit_test.hpp>
#include <fstream>

BOOST_AUTO_TEST_SUITE(test_version)

//BOOST_AUTO_TEST_CASE(test_valid_version) {
//	BOOST_CHECK(version() > 0);
//}
BOOST_AUTO_TEST_CASE(test_md5sum)
{
    std::system("cat ip_filter.tsv | ip_filter | md5sum > readme.txt");

    std::string file_string = "";
    const std::string expected_string = "24e7a7b2270daee89c64d3ca5fb3da1a";
    std::ifstream file("readme.txt");
    if(file.is_open())
    {
        std::getline(file, file_string);
        file.close();
    }
    BOOST_CHECK(file_string == expected_string);
    //BOOST_CHECK(std::strcmp(std::ifstream("readme.txt").rdbuf(), "24e7a7b2270daee89c64d3ca5fb3da1a") == 0);
    std::remove("readme.txt");
}

BOOST_AUTO_TEST_SUITE_END()
