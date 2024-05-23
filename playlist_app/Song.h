//#ifndef SONG_H
//#define SONG_H
//ifndef, define, endif ��ũ�δ� pragma once�� ������ ����
//���� include ����
#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//���, interface������ �̸��� �־ �ǹǷ�
//forward declaration�ص� complie ������ ����.
//��, ����ü(implementation)������ Ŭ������ �����ؾߵȴ�.
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
