#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
using namespace std;

class Memory {
private:
    string name;
    int day_created;

    int layer; // 0 = Working, 1 = Long-term, 2 = Deep
    int state; // 0 = Active, 1 = Faded

    double strength;
    double decay_rate;
    int importance;

    int review_count;
    int dream_count;
    int last_dream_day;

    double dream_bias;
    int suppression_level;

public:
    Memory();

    void initialize(string memory_name, int memory_importance, int current_day, int memories_added_today);

    string getName() const;
    string getLayerName() const;
    string getStateName() const;
    string getSuppressionName() const;
    string getBlurredName() const;
    string getDisplayName() const;

    int getDayCreated() const;
    int getLayer() const;
    int getState() const;
    int getSuppressionLevel() const;

    bool isSuppressed() const;
    bool canBeInnerVoiceCandidate() const;
    bool nameContains(string keyword) const;

    void print(int index) const;
    void printDetail(int index) const;

    void updateLayer();
    void updateFadedState();

    bool review();
    void suppress();
    void applyDailyDecay();

    double urgentScore() const;

    bool passesInnerVoiceChance() const;
    double innerVoiceScore() const;
    void innerVoiceEffect();

    double dreamScore(int current_day) const;
    void dreamEffect(int current_day);
};

#endif