#include <string>
#include <iostream>

#include <SFML/Window.hpp>

#include "libmidi/midi.h"
#include "libmidi/midi_util.h"


using namespace std;


Midi* get_midi_file_from_cli(std::string& filename);
/**
 *
 */
Midi* get_midi_file_from_cli(std::string& filename) {
    try {
        return new Midi(Midi::read_from_file(filename));

    } catch (const MidiError &e) {
        string wrappedDescription = STRING(
            "Problem while loading file: " <<
            filename <<
            "\n"
        ) + e.get_error_description();

        cerr << wrappedDescription << endl;
        filename = "";
        return nullptr;
    }
}



int main(int argc, char *argv[]) {

    string filename;
    if (argc != 2) {
        cerr << "For the time being, you must run linthesia with" <<
            " a filename" <<
            endl;
        return 1;
    }

    filename = string(argv[1]);
    Midi* midi = get_midi_file_from_cli(filename);

    sf::Window window(
        sf::VideoMode(800, 600),
        "Linthesia"
    );


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
    }

    delete midi;

    return 0;
}


