#include <vector>
#include <utility>
#include <iostream>

using Interval = std::pair<int, int>;

bool sortbyFirst(const Interval &a,const Interval &b) 
{ 
    return (a.first < b.first); 
} 

std::vector<Interval> mergeIntervals(std::vector<Interval> intervals)
{

    std::vector<Interval> result;
    // TODO:
    // 1. Handle edge cases
    if(intervals.empty() || intervals.size() == 1) {
        return {};
    }

    // 2. Initialize with first interval
    result.push_back(intervals[0]); 

    // 2. Sort intervals by start
    //now we have the firest values sorted
    std::sort(intervals.begin(), intervals.end(), sortbyFirst);

    // 3. Merge overlapping intervals
    // 3. Merge process
    for (size_t i = 1; i < intervals.size(); i++)
    {
        Interval& last = result.back();
        const Interval& current = intervals[i];

        if (current.first <= last.second)
        {
            // overlap → merge
            last.second = std::max(last.second, current.second);
        }
        else
        {
            // no overlap → add new interval
            result.push_back(current);
        }
    }

    // 4. Return result
    return result;
}

int main () {

    std::vector<Interval> intervals = {
        {1, 3},
        {2, 5},
        {8, 10},
        {9, 12}
    };

    std::vector<Interval> result = mergeIntervals(intervals);

    for (const auto& interval : result)
    {
        std::cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    std::cout << std::endl;

    return 0;
}
