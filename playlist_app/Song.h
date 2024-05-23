//#ifndef SONG_H
//#define SONG_H
//ifndef, define, endif 매크로는 pragma once와 목적이 같다
//이중 include 방지
#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//헤더, interface에서는 이름만 있어도 되므로
//forward declaration해도 complie 문제는 없다.
//단, 구현체(implementation)에서는 클래스를 구현해야된다.
class PlayList;  // forward declaration

class Song {
private:
    int id;    // Each song object has unique id
    string title;   // object member
    string artist;
    string album;
    string mv_url;
    vector<PlayList *> playlists;
    static int id_counter;  // class member

public:
    Song();
    Song(string ti, string ar, string al, string mv);
    ~Song();

    int get_id();
    string get_title();
    string get_artist();

    void print(ostream &out);
    void foutput(ostream& out);

    void register_playlist(PlayList *ptr_plist);
    void unregister_playlist(string plist_name);
    void play();
};

//#endif SONG_H
