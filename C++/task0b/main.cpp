#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
using namespace std;

struct comp
{
    template<typename T>
    bool operator()(const T &l, const T &r) const
    {
        if (l.second != r.second) {
            return l.second > r.second;
        }
 
        return l.first > r.first;
    }
};

int main()
{   
    ifstream fin;
    fin.open("input.txt");
    ofstream fout;
    fout.open("output.csv");

    if (!fin.is_open())
    {
        cout << "Opening input file error" << endl;
        return -1;
    }

    if (!fout.is_open())
    {
        cout << "Opening output file error" << endl;
        return -1;
    }

    map<string, int> words;

    string word;
    int words_count = 0;
    for(fin >> word; !fin.eof(); fin >> word)
    {
        if (word.back() == ',' || word.back() == '.' || word.back() == ':' || word.back() == ';' || word.back() == '!' || word.back() == '?')
        {
            word.erase(word.size() - 1);
        }

        if (words.count(word) == 0)
        {
            words.insert({word, 1});
        }
        else
        {
            words[word] += 1;
        }
        words_count++;
    } 
    
    set<pair<string, int>, comp> words_set(words.begin(), words.end());
    
    fout << "Слово;Частота;Частота (в %)" << '\n';

    for (auto const &pair: words_set) {
        fout << pair.first << ';' << pair.second << ';' << ((double)pair.second / words_count)*100 << '\n';
    }

    fout.close();
    fin.close();
    return 0;
}