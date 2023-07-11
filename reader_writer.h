//
// Created by Kotozzavrik on 08.07.2023.
//

#ifndef YADRO2____READER_WRITER_H
#define YADRO2____READER_WRITER_H

#include <vector>
#include <cstdint>
#include <string>
#include "config.hpp"
#include "tape.h"

class reader_writer {
public:

   static std::vector<std::string> read_tape (  std::string filename,  std::string out_filename, config config_, tape tape );
   static void write_to_tape ( std::vector<std::string> tapes, std::string output, tape output_tape, config config_);
};


#endif //YADRO2____READER_WRITER_H
