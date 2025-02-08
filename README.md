# C++ Audio Player with Playlists 🎵

## Overview
This project is a simple **audio player** built in **C++** using **SFML** for audio playback. It utilizes **doubly linked lists** to manage playlists, allowing users to add, modify, and save playlists. The player can be controlled using keyboard inputs such as the **arrow keys** for navigation and playback control.

## Features
- 📂 **Playlist Management**: Create, modify, and save playlists of surahs or songs.
- 🎵 **Audio Playback**: Supports playing, pausing, and stopping audio files.
- ⏭️ **Navigation Controls**: Use arrow keys to move between tracks.
- 🛠 **Object-Oriented Design**: Implements OOP principles for clean and modular code.
- 🔗 **Doubly Linked List**: Used to efficiently manage the playlist.

## Technologies Used
- **C++** (Programming Language)
- **SFML** (Simple and Fast Multimedia Library) for handling audio playback
- **OOP** (Object-Oriented Programming) concepts
- **Doubly Linked List** (for playlist management)

## Installation & Setup
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/audio-player.git
   cd audio-player
   ```
2. **Install SFML**:
   - Download and install [SFML](https://www.sfml-dev.org/download.php) for your operating system.
   - Make sure to link the SFML libraries correctly in your C++ project.
3. **Compile the Project**:
   - If using **g++**:
     ```bash
     g++ main.cpp -o audio_player -lsfml-audio -lsfml-system
     ```
   - If using **Visual Studio**:
     - Configure project settings to link SFML libraries.
4. **Run the Application**:
   ```bash
   ./audio_player
   ```

## How to Use
- **Add a new track**: Insert a file path to add it to the playlist.
- **Navigate tracks**: Use the **left** and **right** arrow keys to switch between tracks.
- **Play/Pause**: Press **Enter** or **Space** to play/pause the audio.
- **Stop Playback**: Press the **S** key.
- **Modify Playlist**: Manually edit the playlist by adding or removing tracks.

## Project Structure
```
📂 audio-player/
├── 📄 main.cpp        # Main program logic
├── 📄 Playlist.h      # Header file for the Playlist class
├── 📄 Playlist.cpp    # Implementation of Playlist class
├── 📄 Node.h          # Doubly linked list node
├── 🎵 audio/          # Folder containing audio files
├── 📄 README.md       # Project documentation
```

## Future Improvements
- ✅ Add a GUI interface for better user experience.
- ✅ Support different audio formats.
- ✅ Implement volume and playback speed controls.
- ✅ Save and load playlists from a file.

## Contribution
Contributions are welcome! Feel free to fork this repository, submit issues, or create pull requests. 🚀



