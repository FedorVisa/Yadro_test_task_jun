#include <iostream>
#include "config.hpp"
#include "tape.h"
#include "reader_writer.h"
#include "yadroException.hpp"
#include "sort.h"

int main(int argc, char *argv[]) {
    try {
        config config1(argv[1]);
        tape tape1(config1);
        reader_writer::write_to_tape(reader_writer::read_tape(argv[2], argv[3], config1, tape1),"exit.txt", tape1,  config1);
        return 0;

    } catch ( const yadroException& e){
    std::cerr << "Error occurred: " << e.what() << std::endl;
    return 0;
    } catch (const std::exception& e){
    std::cerr << "Some error occurred: " << e.what() <<  std::endl;
    return 0;
    }
}
