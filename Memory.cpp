#include "Memory.h"
#include <iomanip>
#include <cstdlib>

const int FORGET_THRESHOLD = 20;

Memory::Memory() {
    name = "";
    day_created = 0;
    layer = 0;
    state = 0;
    strength = 0;
    decay_rate = 0;
    importance = 0;
    review_count = 0;
    dream_count = 0;
    last_dream_day = -999;
    dream_bias = 0;
    suppression_level = 0;
}

void Memory::initialize(string memory_name, int memory_importance, int current_day, int memories_added_today) {
    name = memory_name;

    if (memory_importance < 1) memory_importance = 1;
    if (memory_importance > 10) memory_importance = 10;
    importance = memory_importance;

    day_created = current_day;
    layer = 0;
    state = 0;

    strength = 50 + importance * 5;
    decay_rate = 5.0;

    if (memories_added_today >= 3) {
        int extra = memories_added_today - 2;
        strength -= extra * 5;
        decay_rate += extra * 0.5;
    }

    if (strength < 30) strength = 30;
    if (strength > 100) strength = 100;

    review_count = 0;
    dream_count = 0;
    last_dream_day = -999;
    dream_bias = 0;
    suppression_level = 0;
}

string Memory::getName() const {
    return name;
}

string Memory::getLayerName() const {
    if (layer == 0) return "Working";
    if (layer == 1) return "Long-term";
    return "Deep";
}

string Memory::getStateName() const {
    if (state == 0) return "Active";
    return "Faded";
}

string Memory::getSuppressionName() const {
    if (suppression_level == 0) return "None";
    if (suppression_level <= 2) return "Mild";
    if (suppression_level <= 4) return "Moderate";
    return "Severe";
}

string Memory::getBlurredName() const {
    string result = name;

    for (int i = 0; i < (int)result.length(); i++) {
        if (result[i] == ' ') continue;

        int letter_pos_in_word = 1;
        for (int j = i - 1; j >= 0 && result[j] != ' '; j--) {
            letter_pos_in_word++;
        }

        bool is_last_letter_in_word = true;
        for (int j = i + 1; j < (int)result.length() && result[j] != ' '; j++) {
            is_last_letter_in_word = false;
            break;
        }

        if (letter_pos_in_word % 2 == 0 && !is_last_letter_in_word) {
            result[i] = '_';
        }
    }

    return result;
}

string Memory::getDisplayName() const {
    if (state == 1 || strength < FORGET_THRESHOLD) {
        return getBlurredName();
    }
    return name;
}

int Memory::getDayCreated() const {
    return day_created;
}

int Memory::getLayer() const {
    return layer;
}

int Memory::getState() const {
    return state;
}

int Memory::getSuppressionLevel() const {
    return suppression_level;
}

bool Memory::isSuppressed() const {
    return suppression_level > 0;
}

bool Memory::canBeInnerVoiceCandidate() const {
    return layer == 2 || state == 1 || suppression_level > 0;
}

bool Memory::nameContains(string keyword) const {
    return name.find(keyword) != string::npos;
}

void Memory::print(int index) const {
    cout << index + 1 << ". "
         << getDisplayName()
         << " | Importance: " << importance
         << " | Strength: " << fixed << setprecision(1) << strength
         << " | Layer: " << getLayerName()
         << " | State: " << getStateName()
         << " | Suppression: " << getSuppressionName()
         << " (" << suppression_level << ")"
         << endl;
}

void Memory::printDetail(int index) const {
    cout << "\n===== Memory Detail =====" << endl;
    cout << "Memory No.: " << index + 1 << endl;
    cout << "Name: " << getDisplayName() << endl;
    cout << "Original Name: " << name << endl;
    cout << "Day Created: " << day_created << endl;
    cout << "Importance: " << importance << endl;
    cout << "Strength: " << fixed << setprecision(1) << strength << endl;
    cout << "Decay Rate: " << fixed << setprecision(1) << decay_rate << endl;
    cout << "Layer: " << getLayerName() << endl;
    cout << "State: " << getStateName() << endl;
    cout << "Suppression: " << getSuppressionName() << " (" << suppression_level << ")" << endl;
    cout << "Review Count: " << review_count << endl;
    cout << "Dream Count: " << dream_count << endl;
}

void Memory::updateLayer() {
    if (review_count >= 5 && importance >= 8) {
        layer = 2;
    }
    else if (review_count >= 2 && layer < 1) {
        layer = 1;
    }
}

void Memory::updateFadedState() {
    if (strength < FORGET_THRESHOLD) {
        state = 1;
    }

    if (state == 1 && strength >= FORGET_THRESHOLD) {
        state = 0;
    }
}

bool Memory::review() {
    bool reduced_suppression = false;

    strength += 20;
    if (strength > 100) strength = 100;

    double reduction = 2.0;
    for (int i = 0; i < review_count; i++) {
        reduction *= 0.5;
    }

    decay_rate -= reduction;
    if (decay_rate < 1.0) {
        decay_rate = 1.0;
    }

    review_count++;

    // Review 是慢速修復：每 2 次 review 才讓 suppression_level 下降 1
    if (review_count % 2 == 0 && suppression_level > 0) {
        suppression_level--;
        reduced_suppression = true;

        dream_bias -= 5;
        if (dream_bias < 0) {
            dream_bias = 0;
        }
    }

    updateLayer();
    updateFadedState();

    return reduced_suppression;
}

void Memory::suppress() {
    suppression_level++;

    // Suppress 是短期逃避：清醒時記憶變弱
    strength -= 10;
    if (strength < 0) {
        strength = 0;
    }

    // 但潛意識與夢境中更容易浮現
    dream_bias += 15 + suppression_level * 3;

    // 壓抑太深時，清醒記憶更不穩定
    if (suppression_level >= 5) {
        decay_rate += 0.5;
    }

    updateFadedState();
}

void Memory::applyDailyDecay() {
    double real_decay = decay_rate;

    if (layer == 1) {
        real_decay *= 0.8;
    }
    else if (layer == 2) {
        real_decay *= 0.5;
    }

    strength -= real_decay;
    if (strength < 0) strength = 0;

    if (dream_bias > 0) {
        dream_bias -= 1;
    }

    updateFadedState();
}

double Memory::urgentScore() const {
    if (suppression_level > 0) {
        return importance * 8 + (100 - strength) - suppression_level * 15;
    }

    return importance * 10 + (100 - strength);
}

bool Memory::passesInnerVoiceChance() const {
    int roll = rand() % 10 + 1;
    return roll <= importance;
}

double Memory::innerVoiceScore() const {
    if (!canBeInnerVoiceCandidate()) return -1;

    double score = importance * 10 + dream_bias;

    if (layer == 2) score += 30;
    if (state == 1) score += 25;
    if (suppression_level > 0) score += suppression_level * 25;

    return score;
}

void Memory::innerVoiceEffect() {
    strength += 5;
    if (strength > 100) strength = 100;

    dream_bias += 10;

    updateFadedState();
}

double Memory::dreamScore(int current_day) const {
    int days_since = current_day - day_created;
    if (days_since < 0) days_since = 0;

    double recency = 30.0 / (days_since + 1);

    double score = recency
                 + strength * 0.3
                 + importance * 3
                 + dream_bias;

    if (layer == 2) score += 30;
    if (state == 1) score += 10;
    if (suppression_level > 0) score += suppression_level * 25;

    bool recently_dreamed = (current_day - last_dream_day <= 2);

    if (recently_dreamed) {
        if (suppression_level > 0) {
            score *= 1.3;
        }
        else if (layer == 2) {
            // deep has no repeated-dream penalty
        }
        else {
            score *= 0.3;
        }
    }

    if (score < 0) score = 0;
    return score;
}

void Memory::dreamEffect(int current_day) {
    dream_count++;
    last_dream_day = current_day;

    strength += 3;
    if (strength > 100) strength = 100;

    if (suppression_level > 0) {
        dream_bias += 5 + suppression_level * 2;
    }

    updateFadedState();
}