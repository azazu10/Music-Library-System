#include "musicLibrary.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Adding a song to the library
void MusicLibrary::addSong(const Song& song) {
    library.push_back(song); // I am using the push_back function from  to add the song to the library
}

// Removing a song by title
bool MusicLibrary::removeSong(const string& title) {
    for (auto it = library.begin(); it != library.end(); ++it) {
        if (it->getTitle() == title) {
            library.erase(it); // I am using the erase function to remove the song from the library
            return true;
        }
    }
    return false;
}

// Editing a song's details
bool MusicLibrary::editSong(const string& title, const Song& updatedSong) {
    for (auto& song : library) {
        if (song.getTitle() == title) {
            song = updatedSong; // I am using the assignment operator to update the song in the library
            return true;
        }
    }
    return false;
}

// Searching for songs by criteria
vector<Song> MusicLibrary::searchSongs(const string& criteria, const string& value) const {
    vector<Song> results;
    
    // I am using the transform function to convert the criteria to lowercase for case-insensitive comparison
    string lowerCriteria = criteria;
    transform(lowerCriteria.begin(), lowerCriteria.end(), lowerCriteria.begin(), ::tolower);

    // I am using the transform function to convert the search value to lowercase
    string lowerValue = value;
    transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), ::tolower);

    for (const auto& song : library) {
        bool match = false;
        string fieldValue;

        if (lowerCriteria == "title") {
            fieldValue = song.getTitle();
        } else if (lowerCriteria == "artist") {
            fieldValue = song.getArtist();
        } else if (lowerCriteria == "album") {
            fieldValue = song.getAlbum();
        } else if (lowerCriteria == "genre") {
            fieldValue = song.getGenre();
        } else if (lowerCriteria == "year") {
            fieldValue = to_string(song.getYear());
        }

        // I am using the transform function to convert the field value to lowercase
        transform(fieldValue.begin(), fieldValue.end(), fieldValue.begin(), ::tolower);

        // I am using the find function to check if the lowercase field value contains the lowercase search value
        if (fieldValue.find(lowerValue) != string::npos) {
            match = true;
        }

        if (match) {
            results.push_back(song);
        }
    }

    return results;
}

// Displaying all songs
void MusicLibrary::displayAllSongs() const {
    if (library.empty()) {
        cout << "The music library is empty.\n";
        return;
    }
    for (const auto& song : library) {
        song.displaySong();
        cout << "----------------------\n";
    }
}

// Saving library to file
void MusicLibrary::saveLibraryToFile(const string& filename) const {
    ofstream outFile(filename); // I am using the ofstream class to create a file stream object
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    for (const auto& song : library) {
        outFile << song.getTitle() << ','
                << song.getArtist() << ','
                << song.getAlbum() << ','
                << song.getGenre() << ','
                << song.getYear() << '\n';
    }
    outFile.close();
    cout << "Library saved to " << filename << "\n";
}

// Loading library from file
void MusicLibrary::loadLibraryFromFile(const string& filename, bool append) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "File does not exist.\n";
        return;
    }
    
    if (!append) {
        library.clear();
    }
    
    string line;
    int lineNumber = 0;
    int added = 0, updated = 0, skipped = 0;
    while (getline(inFile, line)) {
        lineNumber++;
        istringstream iss(line);
        string title, artist, album, genre, yearStr;
        getline(iss, title, ',');
        getline(iss, artist, ',');
        getline(iss, album, ',');
        getline(iss, genre, ',');
        getline(iss, yearStr);
        
        try {
            int year = stoi(yearStr);
            Song song(title, artist, album, genre, year);
            AddResult result = addOrUpdateSong(song, append);
            switch (result) {
                case AddResult::Added: added++; break;
                case AddResult::Updated: updated++; break;
                case AddResult::Skipped: skipped++; break;
            }
        } catch (const invalid_argument& e) {
            cerr << "Error on line " << lineNumber << ": Year '" << yearStr << "' is not an integer.\n";
        } catch (const out_of_range& e) {
            cerr << "Error on line " << lineNumber << ": Year '" << yearStr << "' is out of range for an integer.\n";
        }
    }
    inFile.close();
    cout << "Library processed from " << filename << "\n";
    cout << "Added: " << added << ", Updated: " << updated << ", Skipped: " << skipped << "\n";
}

// Now, I am adding a function to add or update a song to the library. This also handles the case if the song already exists in the library.
MusicLibrary::AddResult MusicLibrary::addOrUpdateSong(const Song& song, bool updateIfExists) {
    auto it = find_if(library.begin(), library.end(),
                      [&song](const Song& s) { return s.getTitle() == song.getTitle() && s.getArtist() == song.getArtist(); });
    //
    if (it != library.end()) {
        if (updateIfExists) {
            *it = song;
            return AddResult::Updated;
        } else {
            return AddResult::Skipped;
        }
    } else {
        library.push_back(song);
        return AddResult::Added;
    }
}

