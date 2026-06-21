#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

std::vector<int> topKElements(const std::vector<int>& nums, size_t k) {
    if (k == 0) return {};
    
    //put the minimum value on the top 
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    for (int x : nums) {
        minHeap.push(x);  // Add the current element to the min-heap
        if (minHeap.size() > k) { 
            // If the size of the min-heap exceeds k, remove the smallest element
            minHeap.pop(); 
        }
    }

    std::vector<int> result;
    result.reserve(minHeap.size());

    while (!minHeap.empty()) {
        // Add the elements from the min-heap to the result vector
        result.push_back(minHeap.top());
        // Remove the smallest element from the min-heap to close the while
        minHeap.pop();
    }

    std::sort(result.rbegin(), result.rend());
    return result;
}

//WRONG IMPLEMENTATION, where try to do it in a hard way
std::vector<int> topKElements_bad(const std::vector<int>& nums, size_t k) {
    
    std::vector<int> aux;

    if(k == 0 || k > nums.size()){
        return {};
    }

    aux.push_back(nums.at(0));

    int auxK = 1;

    for (size_t i = 1; i < nums.size(); i++) {
        if(aux.size() < k){
            if(aux.at(auxK-1) > nums.at(i)){
                aux.push_back(nums.at(i));
            } else {
                int valAux = aux.at(auxK-1);
                aux.at(auxK-1) = nums.at(i);
                aux.push_back(valAux); 
            }
            auxK++;
        } else {
            for (size_t j = k-1; j > 0; j--)
            {
                if(aux.at(j) < nums.at(i) && aux.at(j - 1) > nums.at(i)){
                    aux.insert(aux.begin() + j, nums.at(i));
                }
            }      
        }
    }

    return aux;
}

int main() {

    std::vector<int> values = {5, 1, 9, 2, 7, 3};
    int k = 3;

    std::vector<int> returnV = topKElements(values, k);

    for(int i = 0; i < returnV.size(); i++){
        printf("Value %d = %d\n", i, returnV.at(i));
    }
    return 0;
}
