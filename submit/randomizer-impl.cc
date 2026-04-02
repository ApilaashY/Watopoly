module randomizer;

int Randomizer::randomNum(int min, int max) {

    // Swap the min and max value if min is bigger than max
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }

    return ((*gen)() % (max - min + 1)) + min;
}

int Randomizer::randomNum(int max) {
    if (max > 0) {
        return Randomizer::randomNum(0, max);
    }
    return Randomizer::randomNum(max, 0);
}

void Randomizer::updateSeed(unsigned seedVal) {
    gen = std::make_unique<std::default_random_engine>(seedVal);
}
