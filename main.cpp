#include <iostream>
#include <conio.h>
#include "playlist.cpp"

using namespace std;

void displayMenu()
{
    cout << "===========================================\n";
    cout << "|          Quraan Playlist Manager Menu   |\n";
    cout << "===========================================\n";
    cout << "1. Add a new playlist\n";
    cout << "2. Add Surah to an existing playlist\n";
    cout << "3. Remove Surah from an existing playlist\n";
    cout << "4. Update the order of existing playlist\n";
    cout << "5. Display All Current Playlists\n";
    cout << "6. Display all Playlists Surah\n";
    cout << "7. Display Surah in a specific playlist\n";
    cout << "8. Play Surah from specific playlist\n";
    cout << "   Use left arrow (<-) to play the previous surah\n";
    cout << "   Use right arrow (->) to play the next surah\n";
    cout << "   Use up arrow (^) to pause the current surah\n";
    cout << "   Use down arrow (v) to resume the current surah\n";
    cout << "   Press q to exit current playlist & return back to menu\n";
    cout << "9. Save an existing playlist to a file\n";
    cout << "10. Load an existing playlist from a file\n";
    cout << "11. Remove an existing playlist\n";
    cout << "12. Exit\n";
    cout << "===========================================\n";
    cout << "Your choice: \n"
         << endl;
}

int main()
{
    Doubly_linked_list playlist;
    int choice, pos;
    bool Case = true;
    string director, shaikhName, surahName, type;
    do
    {
        displayMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            cin.ignore();
            cout << "Enter the playlist name: ";
            getline(cin, shaikhName);
            playlist.add_playlist(shaikhName);
            system("pause");
            system("cls");
            break;
        case 2:
            cout << "Enter the playlist name: ";
            playlist.printPlayList();
            cin.ignore();
            getline(cin, shaikhName);
            cout << "Enter surah name: ";
            getline(cin, surahName);
            cout << "Enter director/path: ";
            getline(cin, director);
            cout << "Enter type: ";
            getline(cin, type);
            playlist.add_surah(shaikhName, surahName, director, type);
            system("pause");
            system("cls");
            break;
        case 3:
            cout << "Enter the playlist name: ";
            playlist.printPlayList();
            cin.ignore();
            getline(cin, shaikhName);
            playlist.printSurahs(shaikhName);
            cout << "Enter the surah name: ";
            getline(cin, surahName);
            playlist.removeSurah(shaikhName, surahName);
            system("pause");
            system("cls");
            break;
        case 4:
            cout << "Enter the playlist name: ";
            playlist.printPlayList();
            cin.ignore();
            getline(cin, shaikhName);
            playlist.printSurahs(shaikhName);
            cout << "Enter the surah name: ";
            getline(cin, surahName);
            cout << "Enter the new position: ";
            cin >> pos;
            playlist.modifyPosition(shaikhName, surahName, pos);
            system("pause");
            system("cls");
            break;
        case 5:
            playlist.printPlayList();
            system("pause");
            system("cls");
            break;
        case 6:
            playlist.printAllData();
            system("pause");
            system("cls");
            break;
        case 7:
            cout << "Enter the playlist name: ";
            playlist.printPlayList();
            cin.ignore();
            getline(cin, shaikhName);
            playlist.printSurahs(shaikhName);
            system("pause");
            system("cls");
            break;
        case 8:
            cout << "Enter playlist name: ";
            playlist.printPlayList();
            cin.ignore();
            getline(cin, shaikhName);

            playlist.playShaikhSurahs(shaikhName);
            Case = true;
            while (Case)
            {
                char ch = _getch();
                if (ch == 0 || ch == -32)
                {
                    ch = _getch();
                    switch (ch)
                    {
                    case 75:
                        playlist.playPreviousSurah();
                        break;
                    case 77:
                        playlist.playNextSurah();
                        break;
                    case 72:
                        playlist.pauseCurrentSurah();
                        break;
                    case 80:
                        playlist.resumeCurrentSurah();
                        break;
                    }
                }
                else if (ch == 'q' || ch == 'Q' || ch == 27)
                {
                    Case = false;
                    playlist.StopCurrentSurah();
                    cout << "Exiting to the main menu...\n";
                }
            }
            system("pause");
            system("cls");
            break;

        case 9:
            playlist.saveToFile();
            system("pause");
            system("cls");
            break;
        case 10:
            playlist.loadFrom();
            system("pause");
            system("cls");
            break;
        case 11:
            cout << "Enter playlist to remove: ";
            playlist.printPlayList();
            cin >> shaikhName;
            playlist.removePlayList(shaikhName);
            system("pause");
            system("cls");
            break;
        case 12:
            cout << "Exiting...\n";
            system("pause");
            system("cls");
            break;
        default:
            cout << "Invalid choice or functionality under development.\n";
        }
    } while (choice != 12);
    return 0;
}