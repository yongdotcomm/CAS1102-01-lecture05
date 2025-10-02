#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb/stb_image.h"

void decode_steganography(int image_data[], int data_size, std::string key) {

    int currentIndex = 1000;

    if (data_size <= 0 || key.empty()) return;

    const int keyLen = static_cast<int>(key.size());

    for (int step = 0; ; ++step) {
        // cycle through key characters
        unsigned char kc = static_cast<unsigned char>(key[step % keyLen]);

        // keep jump small but nonzero
        int jump = static_cast<int>(kc % 10) + 1;

        currentIndex += jump;
        if (currentIndex < 0 || currentIndex >= data_size) break;

        int val = image_data[currentIndex];

        if (val == 0) break;

        std::cout << static_cast<char>(val);

        if (step > data_size * 2) break; // safety stop
    }
}

// DO NOT EDIT THE MAIN FUNCTION
int main() {
    const char* image_path = "secret.png";
    int width, height, channels;

    unsigned char* img_data_char = stbi_load(image_path, &width, &height, &channels, 1);

    if (!img_data_char) {
        std::cerr << "❌ Failed to load image: " << image_path << std::endl;
        return 1;
    }

    std::cout << "✅ Loaded " << image_path
              << " width=" << width
              << " height=" << height
              << " channels=" << channels
              << " data_size=" << (width * height) << std::endl;

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
