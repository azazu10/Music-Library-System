#include "song.h"
#include <iostream>

using namespace std;

// Default constructor
Song::Song() : title(""), artist(""), album(""), genre(""), year(0) {}

// Parameterizing the constructor to initialize the song with the given title, artist, album, genre, and year
Song::Song(const string& title, const string& artist,
           const string& album, const string& genre, int year)
    : title(title), artist(artist), album(album), genre(genre), year(year) {}

// Getters
string Song::getTitle() const { return title; }
string Song::getArtist() const { return artist; }
string Song::getAlbum() const { return album; }
string Song::getGenre() const { return genre; }
int Song::getYear() const { return year; }

// Setters
void Song::setTitle(const string& title) { this->title = title; }
void Song::setArtist(const string& artist) { this->artist = artist; }
void Song::setAlbum(const string& album) { this->album = album; }
void Song::setGenre(const string& genre) { this->genre = genre; }
void Song::setYear(int year) { this->year = year; }

// Displaying song details
void Song::displaySong() const {
    cout << "\nTitle: " << title << "\n"
              << "Artist: " << artist << "\n"
              << "Album: " << album << "\n"
              << "Genre: " << genre << "\n"
              << "Year: " << year << "\n";
}
