# Screenshotter
Screenshotter periodically takes screenshots and compares them with the previous screenshot, displaying the percentage of similarity between the two images. The capture and stop functions are triggered by a button.

Screenshotter is written in Qt (C++). The program is cross-platform and can be compiled and run on both Linux and Windows operating systems. SQLite is used as the database.

## Features
- The image comparison with the previous snapshot is performed in a separate thread to avoid blocking the main thread.
- After the comparison and processing of the snapshot, it is displayed in a grid view with an indicator of similarity to the previous snapshot.
- The snapshots, hash sum, and similarity percentage are stored in a database (SQLite). When the program is restarted, these snapshots are loaded into the program.

## Installation
To set up the project, follow these steps:
1. Clone the repository to your local machine.
2. Install the necessary technologies and libraries specified in the project's [Dependencies](#dependencies).
3. Build a project with Qt Creator using the `Screenshotter.pro` file.
4. Compile the project with the Desktop MinGW 64-bit for C++.
5. Now you can run the program using Qt Creator or `.exe` file.

## Dependencies
- Qt (>= 5.15.2) in C++
- DB Browser for SQLite (>= 3.12) (if you are setting up a database): https://github.com/sqlitebrowser/sqlitebrowser/releases
- Desktop MinGW (>= 8.1.0) 64-bit for C++
- Qt Creator (>= 5.0.2) or other IDE

To download Qt, Compiler and IDE, you need to follow the link: https://www.qt.io/download-open-source and download the Qt Online Installer or Qt Source Packages.

## Technologies Used
- Framework: Qt 5.15.2 in C++
- Database: SQLite 3
- Database tool: DB Browser for SQLite 3.12
- Compiler: Desktop MinGW 8.1.0 64-bit for C++
- IDE: Qt Creator 8.0.2

## Screenshots
![screenshot](https://github.com/ShevaMed/Screenshotter/blob/main/screenshots/screen1.png)