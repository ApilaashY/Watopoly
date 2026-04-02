module rollup;

import randomizer;

bool RollUp::addRollUp() {
    if (!reachedMax() && Randomizer::randomNum(CHANCE-1) == 0) {
        issued++;
        return true;
    }
    return false;
}

int RollUp::addRollUp(int amount) {
    // If too many roll ups were added, reduce the amount
    if (issued + amount > MAXISSUED) {
        issued = MAXISSUED;
        return MAXISSUED - issued;
    } else {
        issued += amount;
        return amount;
    }
}

bool RollUp::reachedMax() {
    return issued >= MAXISSUED;
}

void RollUp::usedRollUp() {
    if (issued > 0) issued--;
}
