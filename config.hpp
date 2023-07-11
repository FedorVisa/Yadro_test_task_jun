//
// Created by Kotozzavrik on 06.07.2023.
//

#ifndef YADRO2____CONFIG_HPP
#define YADRO2____CONFIG_HPP

#include <cstdint>
#include <chrono>
#include <string>
class config {
private:
    size_t max_size;
    std::string path = "";
    std::chrono::microseconds write_delay;
    std::chrono::microseconds read_delay;
    std::chrono::microseconds move_delay;
    std::chrono::microseconds rewind_delay;
public:
    config() : write_delay( 0), read_delay(0), move_delay(0), rewind_delay(0) {}
    config( std::string filename);

    void setMaxSize(size_t maxSize) {
        max_size = maxSize;
    }

    void set_write_delay(const std::chrono::microseconds &writeDelay) {
        write_delay = writeDelay;
    }

    void set_read_delay(const std::chrono::microseconds &readDelay) {
        read_delay = readDelay;
    }

    void set_move_delay(const std::chrono::microseconds &moveDelay) {
        move_delay = moveDelay;
    }

    void set_rewind_delay(const std::chrono::microseconds &rewindDelay) {
        rewind_delay = rewindDelay;
    }

    const std::chrono::microseconds &get_write_delay() const {
        return write_delay;
    }

    const std::chrono::microseconds &get_read_delay() const {
        return read_delay;
    }

    const std::chrono::microseconds &get_move_delay() const {
        return move_delay;
    }

    const std::chrono::microseconds &get_rewind_delay() const {
        return rewind_delay;
    }

    size_t get_max_size() const {
        return max_size;
    }

    std::string get_path() const{
        return path;
    }

};


#endif //YADRO2____CONFIG_HPP
