#include <iostream>
#include <vector>
#include <numeric>

int sum(const std::vector<int>& data)
{
    // TODO: implement sequential version first

    //With the loop is not necesary do the check
    // if(data.empty()){
    //     return 0;
    // }

    int result = 0;
    //#pragma parallel reduction (+:sum)
    for(int i : data){
        result += i;
    }

    return result;
}

int main()
{
    std::vector<int> data = {1, 2, 3, 4, 5};

    int result = sum(data);

    std::cout << "Sum: " << result << std::endl;

    return 0;
}