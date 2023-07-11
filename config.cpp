//
// Created by Kotozzavrik on 06.07.2023.
//

#include "config.hpp"
#include "yadroException.hpp"
#include <fstream>
#include <iostream>

config::config(std::string filename) {

    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "File does not exists";
        throw yadroException(yadroException::ExceptionType::FileNotFound);
    }
    file >> this->max_size;
    if ( max_size ==0){
        std::cerr << "wrong configure values";
        throw yadroException(yadroException::ExceptionType::WrongValue);
    }
    file.ignore();
    int t_read,t_write, t_rewind, t_move;
    file >> t_read >> t_write >> t_move >> t_rewind;
    if( t_read <0 || t_write<0 || t_rewind<0 || t_move<0) {
        std::cerr << "wrong configure values";
        throw yadroException(yadroException::ExceptionType::WrongValue);
    }
    set_read_delay( static_cast<std::chrono::milliseconds>(t_read));
    set_write_delay( static_cast<std::chrono::milliseconds>(t_write));
    set_move_delay( static_cast<std::chrono::milliseconds>(t_move));
    set_rewind_delay( static_cast<std::chrono::milliseconds>(t_rewind));
    write_delay/=1000;
    read_delay/=1000;
    rewind_delay/=1000;
    move_delay/=1000;

    std::string tmp_path;
    file >> tmp_path;
    this->path = tmp_path;
    file.close();
}



