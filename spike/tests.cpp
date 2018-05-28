#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

using std::endl;
using std::cout;
using std::string;

const char * TEST_PATH = "./test";

int main ( int argC, char * argV [] ) {
	int returnCode = 0;
    DIR * directory = opendir ( TEST_PATH );
    struct dirent * entry = readdir ( directory );
    while ( entry != NULL ) {
		char * test_name = entry->d_name;
		if ( entry->d_type == DT_DIR && strcmp ( test_name, "." ) != 0 && strcmp ( test_name, ".." ) != 0 ) {
			char source_file [ 255 ];
			char output_file [ 255 ];
			char assert_file [ 255 ];
			char compile_command [ 255 ];
			char diff_command [ 255 ];
			sprintf ( source_file, "%s/%s/main.el", TEST_PATH, test_name );
			sprintf ( output_file, "%s/%s/main.cpp", TEST_PATH, test_name );
			sprintf ( assert_file, "%s/%s/assert.cpp", TEST_PATH, test_name );
			sprintf ( compile_command, "./bin/elc %s > /dev/null 2>&1", source_file );
			sprintf ( diff_command, "diff -qbB %s %s", assert_file, output_file );
			system ( compile_command );
			returnCode += system ( diff_command );
			remove ( output_file );
		}
        entry = readdir ( directory );
    }
    closedir ( directory );
	return returnCode;
}
