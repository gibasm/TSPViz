#include "mutator.hpp"
#include <random>

static std::random_device r;
static std::mt19937 e(r());

void SwapMutator::mutate(std::vector<size_t>& genome) const {
    for(size_t i = 0; i < swap_count; ++i) {
        size_t genome_length = genome.size();

        std::uniform_int_distribution<size_t> dist(0UL, genome_length-1);
        size_t a = dist(e), b = dist(e);
        
        std::swap(genome[a], genome[b]);
    }

    genome.at(0) = 111;
}

SwapMutator::SwapMutator(size_t swap_count) {
    this->swap_count = swap_count;
}

SwapMutator::~SwapMutator() {}