#include <iostream>
#include <string>
#include "musicLibrary.h"
#include "song.h"
#include <algorithm>
#include <regex>

using namespace std;

// Function to display the main menu
void displayMenu() {
    cout << "\nMusic Library System\n";
    cout << "1. Add Song\n";
    cout << "2. Remove Song\n";
    cout << "3. Edit Song\n";
    cout << "4. Search Songs\n";
    cout << "5. Display All Songs\n";
    cout << "6. Save Library\n";
    cout << "7. Load Library\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

// Function to get details for a new song
Song getSongDetails() {
    string title, artist, album, genre;
    int year;

    // Ensuring that the title is not empty
    do {
        cout << "Enter title: ";
        getline(cin, title);
        if (title.empty()) {
            cout << "Error: Title cannot be empty. Please try again.\n";
        }
    } while (title.empty());

    // Ensuring that the artist is not empty
    do {
        cout << "Enter artist: ";
        getline(cin, artist);
        if (artist.empty()) {
            cout << "Error: Artist cannot be empty. Please try again.\n";
        }
    } while (artist.empty());

    cout << "Enter album: ";
    getline(cin, album);
    cout << "Enter genre: ";
    getline(cin, genre);
    
    while (true) {
        string yearStr;
        cout << "Enter year: ";
        getline(cin, yearStr);
        
        try {
            year = stoi(yearStr);
            break;
        } catch (const invalid_argument& e) {
            cerr << "Error: '" << yearStr << "' is not an integer. An year must be an integer. Please enter a valid year.\n";
        } catch (const out_of_range& e) {
            cerr << "Error: '" << yearStr << "' is out of range for an integer. Please try again.\n";
        }
    }

    return Song(title, artist, album, genre, year);
}

int main() {
    MusicLibrary library;

    while (true) {
        displayMenu();
        
        string input;
        getline(cin, input);
        
        // I used regex to check if the input is a valid integer between 1 and 8
        regex integer_expr("^[1-8]$");
        if (!regex_match(input, integer_expr)) {
            cout << "Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }

        int choice = stoi(input);

        // Processing the valid choice
        switch (choice) {
            case 1: {
                // Adding a Song
                Song newSong = getSongDetails();
                MusicLibrary::AddResult result = library.addOrUpdateSong(newSong, false);
                switch (result) {
                    case MusicLibrary::AddResult::Added:
                        cout << "Song added successfully!\n";
                        break;
                    case MusicLibrary::AddResult::Skipped:
                        cout << "Song already exists in the library. Not added.\n";
                        break;
                    default:
                        // This shouldn't happen when updateIfExists is false
                        cout << "Unexpected result when adding song.\n";
                        break;
                }
                break;
            }
            case 2: {
                // Removing a Song
                string title;
                cout << "Enter the title of the song to remove: ";
                getline(cin, title);
                if (library.removeSong(title)) {
                    cout << "Song removed successfully!\n";
                } else {
                    cout << "Song not found.\n";
                }
                break;
            }
            case 3: {
                // Editing a Song
                string title;
                cout << "Enter the title of the song to edit: ";
                getline(cin, title);
                if (library.songExists(title)) {
                    Song updatedSong = getSongDetails();
                    if (library.editSong(title, updatedSong)) {
                        cout << "Song updated successfully!\n";
                    } else {
                        cout << "Error updating song.\n";
                    }
                } else {
                    cout << "Song not found.\n";
                }
                break;
            }
            case 4: {
                // Searching Songs
                string criteria, value;
                cout << "Search by (title/artist/album/genre/year): ";
                getline(cin, criteria);
                
                // I used transform to convert the criteria to lowercase to make the search case-insensitive
                transform(criteria.begin(), criteria.end(), criteria.begin(), ::tolower);
                
                if (criteria != "title" && criteria != "artist" && criteria != "album" && 
                    criteria != "genre" && criteria != "year") {
                    cout << "Error: Invalid search criteria. Please choose from title, artist, album, genre, or year.\n";
                    break;
                }
                
                cout << "Enter the " << criteria << ": ";
                getline(cin, value);
                vector<Song> results = library.searchSongs(criteria, value); // Storing songs in a vector after the search
                if (results.empty()) {
                    cout << "No songs found matching the criteria.\n";
                } else {
                    for (const auto& song : results) {
                        song.displaySong();
                        cout << "----------------------\n";
                    }
                }
                break;
            }
            case 5:
                // Displaying All Songs
                library.displayAllSongs();
                break;
            case 6: {
                // Saving Library
                string filename;
                cout << "Enter filename to save: ";
                getline(cin, filename);
                library.saveLibraryToFile(filename);
                break;
            }
            case 7: {
                // Loading Library
                string filename;
                cout << "Enter filename to load: ";
                getline(cin, filename);
                
                // Over here, I am giving the user the option to add to the existing library or replace it
                char choice;
                cout << "Do you want to (a)dd to the existing library or (r)eplace it? (a/r): ";
                cin >> choice;
                cin.ignore(); // Clearing the newline character

                // I am using the tolower function to convert the choice to lowercase
                bool append = false;
                if (tolower(choice) == 'a') {
                    append = true;
                } else if (tolower(choice) != 'r') {
                    cout << "Invalid choice. Defaulting to replace.\n";
                }
                
                library.loadLibraryFromFile(filename, append);
                break;
            }
            case 8:
                cout << "Exiting program. Goodbye!\n";
                return 0;
        }
    }

    return 0;
}
