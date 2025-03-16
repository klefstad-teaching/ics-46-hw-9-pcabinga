#include "ladder.h"

void error(string word1, string word2, string msg){
    cout << "Problem with " << word1 << " and " << word2 << " because " << msg;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){

    int len1 = str1.size();
    int len2 = str2.size();

    if(abs(len1 - len2) > d) return false;

    int count = 0;

    int i = 0, j = 0;
    while(i < len1 && j < len2){
        if(str1[i] != str2[j]){ 
            ++count;
            if(count > d) return false; 
     

            if(len1 > len2) ++i;
            else if(len2 > len1) ++j;
            else{
                ++i;
                ++j;
            }
        } else{
            ++i;
            ++j;
        }

    }
    count += (len1 - i) + (len2 - j);
    return count <= d;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();
        for(auto word : word_list){
            if (is_adjacent(last_word,word)){
                if(visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                     new_ladder.push_back(word);

                     if(word == end_word){
                        return new_ladder;
                     }

                     ladder_queue.push(new_ladder);
                    
                }
            }
        }
    }

    return {};

}
void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    string word;

    while(in>>word){
        word_list.insert(word);
    }

    in.close(); 

}
void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for(size_t i = 0; i < ladder.size(); ++i){
       cout << ladder[i] << " " ;
    }
    cout << endl;

}
void verify_word_ladder(){
    
}