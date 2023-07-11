//
// Created by Kotozzavrik on 06.07.2023.
//

#include <iostream>
#include <fstream>
#include <thread>
#include "tape.h"
#include "yadroException.hpp"


tape::tape(const tape& other)
        : size(other.size),
          tape_(other.tape_),
          write_delay(other.write_delay),
          read_delay(other.read_delay),
          move_delay(other.move_delay),
          rewind_delay(other.rewind_delay){
            this->name = generate_unique_name();
}


tape::tape( config config_file):
write_delay(config_file.get_write_delay()),
move_delay(config_file.get_move_delay()),
read_delay(config_file.get_read_delay()),
rewind_delay(config_file.get_rewind_delay()),
size(config_file.get_max_size()){}

void tape::add_to_tape(int32_t value) {
    this->tape_.push_back(value);
}

size_t tape::get_curr_pos() {
    return this->curr_position;
}

size_t tape::get_size() {
    return this->tape_.size();
}

std::string tape::get_filename(){
    return  this->name;
}

std::vector <int32_t> tape::get_values(){
    return this->tape_;
}


void  tape::read( int32_t value){
    this->tape_.push_back(value);

};
void tape::read( std::fstream& file, int32_t value) {
    this->tape_.push_back(value);
    std::this_thread::sleep_for(read_delay);
}

void tape::write(std::fstream& file  ) {
    file << tape_[curr_position] << " ";
    std::this_thread::sleep_for(write_delay);
}

void  tape::move_right (){
    this->curr_position++;
    std::this_thread::sleep_for(move_delay);
}

void  tape::move_left (){
    if(this->curr_position == 0){
        std::cerr << "Cant move left.";
        throw yadroException(yadroException::ExceptionType::WrongPositioning);
    }
    this->curr_position--;
    std::this_thread::sleep_for(move_delay);
}
void  tape::rewind_tape(){
    this->curr_position =0;
    std::this_thread::sleep_for(rewind_delay);
}

std::string tape::generate_unique_name() const {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::system_clock::to_time_t(now);
    std::string name = std::to_string(timestamp)+ ".txt";
    return name;
}





