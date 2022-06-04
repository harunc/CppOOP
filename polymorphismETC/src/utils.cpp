//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname:Harun Çifci
//---Student Number:150180089
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include "utils.h"

StatisticalDistribution *choose_function(int distType)
{
    if (distType == 0)
    {
        StatisticalDistribution *normalDist = new NormalDistribution();
        return normalDist;
    }
    else if (distType == 1)
    {
        StatisticalDistribution *uniformDist = new UniformDistribution();
        return uniformDist;
    }
    else if (distType == 2)
    {
        StatisticalDistribution *exponentialDist = new ExponentialDistribution();
        return exponentialDist;
    }
    else
    {
        throw "Unidentified distribution function!";
    }
    return NULL;
}

double many_trials(StatisticalDistribution *dist, std::vector<double> random_sample, double t_value, int trials, int sample_size, int seed_value)
{
    int success = 0;
    int i = 0;
    while (i < trials)
    {
        std::vector<double> random_sample = dist->sample(sample_size, seed_value);
        std::vector<double> confidence_interval = dist->calculate_confidence_interval(random_sample, sample_size, t_value);
        if (confidence_interval[0] < dist->getMean() && confidence_interval[2] > dist->getMean())
        {
            success++;
        }
        seed_value++;
        i++;
    }
    return (double(success) / double(trials));
}
