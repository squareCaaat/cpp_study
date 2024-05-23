#include <fstream>
#include <sstream>
#include "Song.h"
#include "PlayList.h"
// problem include가 중복된다.
// 예상 문제 변수, 클래스의 중복 선언이 될 수도 있다.
// 따라서 pragma once 지시어를 사용한다.
using namespace std;

PlayList::PlayList(string str): name(str) {
}

string PlayList::get_name() {
    return name;
}

void PlayList::add_song(Song *song) {
    tracks.push_back(song);
    song->register_playlist(this);
}

void PlayList::print(ostream &out) {
    out << name << ":" << endl;
    for (auto song_ptr: tracks) {
        song_ptr->print(out);
        out << endl;
    }
}

void PlayList::foutput(ostream& out) {
    for (auto song_ptr : tracks) {
        song_ptr->foutput(out);
        out << endl;
    }
}

vector<Song *> PlayList::find_songs_by_keyword(string keyword) {
    vector<Song *> result;
    for (Song *item: tracks) {
        if (item->get_title().find(keyword) != string::npos || item->get_artist().find(keyword) != string::npos )
            result.push_back(item);
    }
    return result;
}

Song *PlayList::find_song_by_id(int sid) {
    for (auto item: tracks)
        if (item->get_id() == sid)
            return item;
    return nullptr;
}

void PlayList::delete_song_by_id(int songId) {
    for (auto it=tracks.begin(); it != tracks.end(); it++) {
        if ((*it)->get_id() == songId) {
            tracks.erase(it);
            return;
        }
    }
}

void PlayList::clear_songs() {
    for (auto it=tracks.begin(); it != tracks.end(); it++)
        (*it)->unregister_playlist(name);
    tracks.clear();  // unnecessary
}

int PlayList::size() {
    return tracks.size();
}
