//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname:Harun Çifci
//---Student Number:150180089
//--------------------------//

#ifndef __STATISTICS_H
#define __STATISTICS_H

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include <vector>

class StatisticalDistribution
{
private:
    double mean;
    friend class NormalDistribution;
    friend class UniformDistribution;
    friend class ExponentialDistribution;

public:
    double getMean();
    void setMean(double);
    virtual std::vector<double> sample(int, int) = 0;
    std::vector<double> calculate_confidence_interval(std::vector<double> randomSample, int sampleSize, double tValue);
};

class NormalDistribution : public StatisticalDistribution
{
private:
    double stddev;

public:
    NormalDistribution();
    std::vector<double> sample(int, int);
};

class UniformDistribution : public StatisticalDistribution
{
private:
    double a;
    double b;

public:
    UniformDistribution();
    std::vector<double> sample(int, int);
};
class ExponentialDistribution : public StatisticalDistribution
{
private:
    double lambda;

public:
    ExponentialDistribution();
    std::vector<double> sample(int, int);
};
#endif
