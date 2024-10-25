#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <vector>
#include <string>
#include <algorithm> // For find_if
#include "song.h"

using namespace std;

// The MusicLibrary class manages a collection of songs
class MusicLibrary {
private:
    vector<Song> library;

public:
    // Adding a song to the library
    void addSong(const Song& song);

    // Removing a song by title
    bool removeSong(const string& title);

    // Editing a song's details
    bool editSong(const string& title, const Song& updatedSong);

    // Searching for songs by criteria
    vector<Song> searchSongs(const string& criteria, const string& value) const;

    // Displaying all songs
    void displayAllSongs() const;

    // Saving library to file
    void saveLibraryToFile(const string& filename) const;

    // Loading library from file
    void loadLibraryFromFile(const string& filename, bool append = false);

    // Checking if a song exists by title
    bool songExists(const string& title) const {
        return find_if(library.begin(), library.end(),
                             [&title](const Song& s) { return s.getTitle() == title; }) != library.end();
    }

    // Adding, updating or skipping a song, handling duplicates
    enum class AddResult { Added, Updated, Skipped };
    AddResult addOrUpdateSong(const Song& song, bool updateIfExists);
};

#endif // MUSICLIBRARY_H
