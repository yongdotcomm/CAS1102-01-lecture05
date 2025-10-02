#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb/stb_image.h"

void decode_steganography(int image_data[], int data_size, std::string key) {

    int currentIndex = 1000;

    // TODO: Implement the solve_steganography function.
    /**
     * Implement a loop to decrypt the message, starting from index 1000.
     *
     * Every character is just a number (its ASCII code).
     * Type casting allows you to switch between these two views.
     *
     * - To get a number from a character: (int)key_char
     *   Example: (int)'A' results in the integer 65.
     * - To get a character from a number: (char)secret_value
     *   Example: (char)65 results in the character 'A'.
     *
     * The decryption process is as follows:
     * - Use the ASCII value of the repeating `key` characters to determine the jump distance.
     *   (Hint: use the modulo '%' operator).
     * - Update your current index with the jump distance, then read the value from `image_data`.
     *   Remember to always stay within the array bounds!
     * - If the value is 0, stop the loop. Otherwise, cast the value to a `char` and print it.
     */

    if (data_size <= 0 || key.empty()) return;

    const int keyLen = static_cast<int>(key.size());
    int steps = 0;

    // Safety cap to avoid infinite loops if data is malformed
    const int max_steps = data_size * 2;

    while (steps < max_steps) {
        // Use ASCII of repeating key chars as jump distance
        int jump = static_cast<unsigned char>(key[steps % keyLen]);

        // Ensure we always move forward at least 1
        if (jump == 0) jump = 1;

        // Move and wrap within bounds
        currentIndex = (currentIndex + jump) % data_size;

        int val = image_data[currentIndex];

        // 0 marks the end of the hidden message
        if (val == 0) break;

        std::cout << static_cast<char>(val);
        ++steps;
    }
}


// DO NOT EDIT THE MAIN FUNCTION
int main() {
    const char* image_path = "secret.png";
    int width, height, channels;

    unsigned char* img_data_char = stbi_load(image_path, &width, &height, &channels, 1);

    int data_size = width * height;

    int* image_data_int = new int[data_size];
    for (int i = 0; i < data_size; ++i) {
        image_data_int[i] = (int)img_data_char[i];
    }

    stbi_image_free(img_data_char);

    std::string user_key;
    std::cout << "Of the four pillars of OOP, what is the principle of separating interface and implementation? (First letter capitalized): ";
    std::cin >> user_key;

    std::cout << "------------------------------------------" << std::endl;
    decode_steganography(image_data_int, data_size, user_key);
    std::cout << "\n------------------------------------------" << std::endl;

    delete[] image_data_int;

    return 0;
}
