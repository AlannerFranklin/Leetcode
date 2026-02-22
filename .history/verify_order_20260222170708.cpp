#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

void printVectorAndBinary(int n) {
    std::cout << "Number: " << n << std::endl;
    
    // Standard binary representation (MSB to LSB)
    std::string binary = std::bitset<8>(n).to_string();
    // Remove leading zeros for clarity
    size_t firstOne = binary.find('1');
    if (firstOne != std::string::npos) {
        binary = binary.substr(firstOne);
    }
    std::cout << "Binary string (MSB -> LSB): " << binary << std::endl;

    // User's vector logic
    std::vector<int> nums;
    int tempN = n;
    while (tempN > 0) {
        nums.push_back(tempN % 2);
        tempN /= 2;
    }

    std::cout << "Vector content (index 0 -> end): [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;
    
    std::cout << "Indices of '1' in vector: ";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == 1) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl << "-------------------" << std::endl;
}

int main() {
    printVectorAndBinary(22); // 10110
    printVectorAndBinary(8);  // 1000
    printVectorAndBinary(5);  // 101
    return 0;
}
