#include <iostream>
#include <string>
using namespace std;

const int MAX_MEMORY = 100;
const int FORGET_THRESHOLD = 20;

struct Memory {
    string name;

    int day_created;
    int layer; // 0 = working, 1 = long-term, 2 = deep
    int state; // 0 = active, 1 = suppressed, 2 = faded

    double strength;
    double decay_rate;
    int importance; // 建立時設定，之後不改

    int review_count;
    int dream_count;
    int last_dream_day;
};

int main() {
    cout << "DreamCore Memory System started!" << endl;
    return 0;
}