#pragma once

class Interval
{
private:
    /* data */
public:
    int start;
    int end;
    Interval(int mStart, int mEnd);
    ~Interval();
};

Interval::Interval(int mStart, int mEnd)
{
    this->end = mEnd;
    this->start = mStart;
}

Interval::~Interval()
{
}
