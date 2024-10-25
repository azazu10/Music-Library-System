#ifndef SONG_H
#define SONG_H

#include <string>

using namespace std;

class  Song {
private:
    string title;
    string artist;
    string album;
    string genre;
    int year;

public:
    // Constructors
    Song();
    Song(const string& title, const string& artist,
         const string& album, const string& genre, int year);

    // Getters
    string getTitle() const;
    string getArtist() const;
    string getAlbum() const;
    string getGenre() const;
    int getYear() const;

    // Setters
    void setTitle(const string& title);
    void setArtist(const string& artist);
    void setAlbum(const string& album);
    void setGenre(const string& genre);
    void setYear(int year);

    // Displaying song details
    void displaySong() const;
};

#endif // SONG_H
