#ifndef _UTILS_RANDOM_SAMPLER_H_
#define _UTILS_RANDOM_SAMPLER_H_

#include "utils/random/Randomizer.h"

namespace Utils
{

/****************************
 * SAMPLES GENERATION
 ****************************/
template < class Data >
class Sampler
{
public:
    Sampler()
        : randomizer_(Randomizer::instance())
    {
    }

    Data make();

private:
    Randomizer& randomizer_;
};

};

#endif
