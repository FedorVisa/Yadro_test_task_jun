
#ifndef YADRO2____TAPE_H
#define YADRO2____TAPE_H

#include "config.hpp"

#include <vector>
#include <fstream>

class tape {
private:
    size_t size;
    size_t curr_position=0;
    std::string name= "";
    std::vector <int32_t> tape_;
    std::chrono::microseconds write_delay;
    std::chrono::microseconds read_delay;
    std::chrono::microseconds move_delay;
    std::chrono::microseconds rewind_delay;
public:
    tape(): write_delay( 0), read_delay(0), move_delay(0), rewind_delay(0) {}

    tape( const tape& a);

    tape( config config_file);

    void set_size(size_t size) {
        this->size = size;
    }

    void set_write_delay(const std::chrono::microseconds &writeDelay) {
        this->write_delay = writeDelay;
    }

    void set_read_delay(const std::chrono::microseconds &readDelay) {
        this->read_delay = readDelay;
    }

    void set_rewind_delay(const std::chrono::microseconds &rewindDelay) {
        this->rewind_delay = rewindDelay;
    }
    void set_move_delay(const std::chrono::microseconds &moveDelay){
        this->move_delay = moveDelay;
    }
    void set_name(const std::string name){
        this->name = name;
    }
    void set_vector( std::vector<int32_t> other){
        this->tape_= other;
    }
    size_t get_size();
    std::string get_filename();
    size_t get_curr_pos();
    std::vector <int32_t> get_values();


    void read_tape( const std::string input_file);
    void write_tape ( const std::string output_file);
    void read_config (const std::string config_file);
  //  void write ( std::fstream& file);
    void read ( int32_t value);
    void read( std::fstream& file, int32_t value );
    void write( std::fstream& file);
    void add_to_tape(int32_t value);
    void move_right ();
    void move_left ();
    void rewind_tape();
    std::string generate_unique_name() const;




};


#endif //YADRO2____TAPE_H
