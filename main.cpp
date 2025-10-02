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

// --- DEBUG VERSION: paste under the TODO to see what's happening ---
if (data_size <= 0 || key.empty()) {
    std::cerr << "[Debug] data_size <= 0 or empty key\n";
    return;
}

int currentIndex = 1000 % data_size;
std::size_t keyPos = 0;

const int hard_cap_steps = std::max(40, data_size > 0 ? data_size / 50 : 40); // print a handful of steps
int printed_chars = 0;
int zeros_in_a_row = 0;

std::cerr << "[Debug] data_size=" << data_size << " startIdx=" << currentIndex
          << " key=\"" << key << "\" (len=" << key.size() << ")\n";

for (int step = 0; step < hard_cap_steps; ++step) {
    unsigned char k = static_cast<unsigned char>(key[keyPos]);
    int jump = static_cast<int>(k % data_size);
    int nextIndex = (currentIndex + jump) % data_size;
    int value = image_data[nextIndex];

    std::cerr << "[Debug] step=" << step
              << " key[" << keyPos << "]='" << key[keyPos] << "'(" << (int)k << ")"
              << " jump=" << jump
              << " idx " << currentIndex << "->" << nextIndex
              << " value=" << value << "\n";

    currentIndex = nextIndex;
    keyPos = (keyPos + 1) % key.size();

    if (value == 0) {
        ++zeros_in_a_row;
        if (zeros_in_a_row >= 2) {
            std::cerr << "[Debug] two consecutive zeros; likely end or wrong key.\n";
            break;
        }
        continue; // don't print a char for zero
    } else {
        zeros_in_a_row = 0;
    }

    std::cout << static_cast<char>(value);
    ++printed_chars;
}

// flush so you can see partial output
std::cout.flush();
std::cerr << "[Debug] printed_chars=" << printed_chars << "\n";
// --- END DEBUG VERSION ---


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
