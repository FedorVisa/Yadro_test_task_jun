//
// Created by Kotozzavrik on 08.07.2023.
//

#include "reader_writer.h"
#include "yadroException.hpp"
#include "sort.h"
#include "tape.h"
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <filesystem>



std::vector<int32_t> sort_block(std::vector<int32_t>& block) {
    sort::my_merge( block,0, block.size()-1);
    return block;
}


std::vector<std::string> reader_writer::read_tape(std::string inputFilename, std::string outputFilename, config config_, tape tape1) {

    std::fstream input_file(inputFilename);
    if(!input_file.is_open()){
        std::cerr << "File does not exists";
        throw yadroException(yadroException::ExceptionType::FileNotFound);
    }
    int num;
    int block_num=0;
    std::vector<int32_t> sequence;
    std::vector<std::string> filenames;


    while (input_file >> num) {
        sequence.push_back(num);
        tape1.read(input_file, num);
        tape1.move_right();

        if (sequence.size() == config_.get_max_size()) {

            std::vector<int32_t> sortedBlock = sort_block(sequence);
            block_num++;
            tape1.set_vector(sortedBlock);
            tape tape_tmp(tape1);
            std::fstream output_file(config_.get_path()+ "\\" +std::to_string(block_num)+ tape_tmp.get_filename(), std::ios::app);

            for (int num : tape_tmp.get_values()) {
                tape_tmp.write( output_file);
                tape_tmp.move_right();
            }
            filenames.push_back(config_.get_path()+ "\\" +std::to_string(block_num)+ tape_tmp.get_filename());
            output_file.close();
            sequence.clear();
        }
    }


    if (!sequence.empty()) {
        tape tape_tmp(tape1);
        std::vector<int> sortedBlock = sort_block(sequence);
        block_num++;
        std::ofstream output_file(config_.get_path()+ "\\" +std::to_string(block_num)+ tape_tmp.get_filename(), std::ios::app);
        for (int num : sortedBlock) {
            output_file << num << " ";
        }
        filenames.push_back(config_.get_path()+ "\\" +std::to_string(block_num)+ tape_tmp.get_filename());
        output_file.close();
    }

    input_file.close();
    return filenames;
}

void reader_writer::write_to_tape(std::vector<std::string> tapes, std::string output, tape output_tape, config config_) {

    std::vector<std::fstream> streams;
    for (const auto &unit: tapes) {
        std::fstream sorted_stream(unit);
        streams.push_back(std::move(sorted_stream));
    }

    int value;
    std::srand(static_cast<unsigned>(std::time(0)));
    while (tapes.size() > 1) {
        std::vector<std::string> new_temp_files;
        for (int i = 0; i < tapes.size(); i += 2) {
            std::ifstream file1(tapes[i]);
            std::ifstream file2(tapes[i + 1]);
            std::string newTempFile =
                    config_.get_path() + "\\" + "temp_" + std::to_string(std::rand()%1000) +
                    ".txt";
            std::ofstream tempOutput(newTempFile);
            if (!tempOutput) {
                std::cerr << "File does not exists ";
                throw yadroException(yadroException::ExceptionType::FileNotFound);
            }
            int num1, num2;
            file1 >> num1;
            file2 >> num2;
            while (file1 && file2) {
                if (num1 <= num2) {
                    tempOutput << num1 << " ";
                    file1 >> num1;
                } else {
                    tempOutput << num2 << " ";
                    file2 >> num2;
                }
            }
            while (file1) {
                tempOutput << num1 << " ";
                file1 >> num1;
            }

            while (file2) {
                tempOutput << num2 << " ";
                file2 >> num2;
            }
            file1.close();
            file2.close();
            tempOutput.close();
            new_temp_files.push_back(newTempFile);
        }
        for (const std::string& tempFile : tapes) {
            std::remove(tempFile.c_str());
        }

        tapes = new_temp_files;
    }

    std::fstream sorted( tapes[0] );

    if (!sorted.is_open()) {
        std::cerr << "File does not exists";
        throw yadroException(yadroException::ExceptionType::FileNotFound);
    }

    std::fstream output_file(output, std::ios::app);
    output_tape.set_name(output);
    if (!output_file.is_open()) {
        std::cerr << "File does not exists";
        throw yadroException(yadroException::ExceptionType::FileNotFound);
    }
    while( sorted >> value) {
        output_tape.read(value);
        output_tape.write(output_file);
        output_tape.move_right();

    }
    sorted.close();
    output_file.close();
}

