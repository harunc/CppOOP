//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname:Harun Çifci
//---Student Number:150180089
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include "statistics.h"
#include <random>
#include <iostream>
//-----------------Constructors--------------//
NormalDistribution::NormalDistribution()
{
    this->mean = 0.0;
    this->stddev = 1.0;
}
UniformDistribution::UniformDistribution()
{
    this->mean = 0.0;
    this->a = -1.0;
    this->b = 1.0;
}
ExponentialDistribution::ExponentialDistribution()
{
    this->mean = 1.0;
    this->lambda = 1.0;
}
//------------------Getters/Setters--------------//
double StatisticalDistribution::getMean()
{
    return this->mean;
}
void StatisticalDistribution::setMean(double Mean)
{
    this->mean = Mean;
}
//------------------Calculate CI--------------//
std::vector<double> StatisticalDistribution::calculate_confidence_interval(std::vector<double> randomSample, int sampleSize, double tValue)
{
    double sum = 0;
    for (std::vector<double>::iterator i = randomSample.begin(); i != randomSample.end(); ++i)
    {
        sum += *i;
    }
    double mean = sum / randomSample.size(); // mean
    double deviation = std::inner_product(randomSample.begin(), randomSample.end(), randomSample.begin(), 0.0f);
    double standardDeviation = sqrt(deviation / randomSample.size() - (mean * mean));
    double lowerBound = mean - (tValue * (standardDeviation / std::sqrt(sampleSize)));
    double upperBound = mean + (tValue * (standardDeviation / std::sqrt(sampleSize)));
    std::vector<double> confidenceInterval = {lowerBound, mean, upperBound};

    return confidenceInterval;
}

//------------------SAMPLE FUNCS--------------//
std::vector<double> NormalDistribution::sample(int sampleSize, int seedValue)
{
    std::vector<double> NormalDistributionSample;
    std::default_random_engine generator;
    generator.seed(seedValue);
    std::normal_distribution<double> distribution(this->getMean(), this->stddev);

    for (int i = 0; i < sampleSize; i++)
    {
        double number = distribution(generator);
        NormalDistributionSample.push_back(number);
    }
    return NormalDistributionSample;
}
std::vector<double> UniformDistribution::sample(int sampleSize, int seedValue)
{
    std::vector<double> UniformDistributionSample;
    std::default_random_engine generator;
    generator.seed(seedValue);
    std::uniform_real_distribution<double> distribution(this->a, this->b);

    for (int i = 0; i < sampleSize; i++)
    {
        double number = distribution(generator);
        UniformDistributionSample.push_back(number);
    }
    return UniformDistributionSample;
}
std::vector<double> ExponentialDistribution::sample(int sampleSize, int seedValue)
{
    std::vector<double> ExponentialDistributionSample;
    std::default_random_engine generator;
    generator.seed(seedValue);
    std::exponential_distribution<double> distribution(this->lambda);

    for (int i = 0; i < sampleSize; i++)
    {
        double number = distribution(generator);
        ExponentialDistributionSample.push_back(number);
    }
    return ExponentialDistributionSample;
}