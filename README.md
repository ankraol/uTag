# uTag

An app to read and write tags of mp3 files.
    - accepts a directory as a command-line argument;
    - defines audio file format by extension .mp3;
    - displays a list of audio-file names in the requested directory;
    - displays only audio-file formats supported by the app;
    - displays/edits these audio file tags in the GUI window:
        - Artist;
        - Title;
        - Album;
        - Genre;
        - Audio file path (not editable);
    - supports audio files items sorting in alphabetical (asc/desc) order by a certain tag;
    
## Installation

As the app uses gtkmm for UI, it is recommended to install gtkmm:
    [tutorial] (https://gtkmm-tutorial.blogspot.com/p/gtkmm-installation.html) <- to install gtkmm;
    
## Usage

First, build an app:
```shell script
    bash ./build.sh
```

You can either put a directory name as a command-line argument:
```shell script
    ./utag [dirName]
```
or just execute an app:
```shell script
    ./utag
```

