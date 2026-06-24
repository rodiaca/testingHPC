#include <iostream>
#include <vector>
#include <cstdint>

std::vector<uint8_t> boxBlur(
    const std::vector<uint8_t>& image,
    int width,
    int height)
{
    // TODO
    std::vector<uint8_t> result(width * height);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            
            //loop for the x
            int sum = 0;
            int count = 0;
            for(int k = -1; k <= 1; k++){ //for y
                int i_2 = i + k;
                if(i_2 < 0 || i_2 >= height){
                    continue;      
                }

                for(int e = -1; e <= 1; e++){ //for x
                    int j_2 = j + e;

                    if(j_2 < 0 || j_2 >= width){
                        continue;
                    }
                    sum += image[i_2 * width + j_2];
                    count++;
                }
            }

            result[i * width + j] = sum / count;
            
        }
    }

    

    return result;
}

void printImage(const std::vector<uint8_t>& img, int width, int height)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            std::cout << static_cast<int>(img[i * width + j]) << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    int width = 3;
    int height = 3;

    std::vector<uint8_t> image = {
        10, 10, 10,
        10, 50, 10,
        10, 10, 10
    };

    auto result = boxBlur(image, width, height);

    std::cout << "Input:\n";
    printImage(image, width, height);

    std::cout << "\nOutput:\n";
    printImage(result, width, height);

    return 0;
}