// Task 1 - Load a 512x512 image lena.raw
//        - Apply specified per-pixel transformation to each pixel
//        - Save as result.raw
#include <fstream>
#include <iostream>
#include <vector>

// Size of the framebuffer
const unsigned int SIZE = 512;

// A simple RGB struct will represent a pixel in the framebuffer
struct Pixel {
    // TODO: Define correct data type for r, g, b channel
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int clamp(double number) {
    if (number > 255) return 255;
    else if (number < 0) return 0;
    else return number;
}

int main() {
    // Initialize a framebuffer
    auto framebuffer = new Pixel[SIZE][SIZE];

    // TODO: Open file lena.raw (this is 512x512 RAW GRB format)
    std::ifstream infile("C:\\Users\\tomco\\Documents\\School\\ZS 2022-23\\PPGSO\\repo\\cmake-build-debug\\lena.raw",
                         std::ios::binary);

    // TODO: Read data to framebuffer and close the file
    infile.read(reinterpret_cast<char *>(framebuffer), sizeof(Pixel) * SIZE * SIZE);
    infile.close();

    // Traverse the framebuffer
    for (unsigned int y = 0; y < SIZE; y++) {
        for (unsigned int x = 0; x < SIZE; x++) {
            // TODO: Apply pixel operation
            int noiseStrength = 0;
            if (x < SIZE / 2 && y < SIZE / 2) noiseStrength = 50;
            else if (x > SIZE / 2 && y < SIZE / 2) noiseStrength = 80;
            else if (x < SIZE / 2 && y > SIZE / 2) noiseStrength = 120;
            else noiseStrength = 150;

            float randomRateR = rand() % noiseStrength;
            float randomRateG = rand() % noiseStrength;
            float randomRateB = rand() % noiseStrength;

            framebuffer[y][x].r = clamp(framebuffer[y][x].r + randomRateR);
            framebuffer[y][x].g = clamp(framebuffer[y][x].g + randomRateG);
            framebuffer[y][x].b = clamp(framebuffer[y][x].b + randomRateB);
        }
    }

    // TODO: Open file result.raw
    std::ofstream resultFile("result.raw", std::ios::binary);

    std::cout << "Generating result.raw file ..." << std::endl;

    // TODO: Write the framebuffer to the file and close it
    resultFile.write(reinterpret_cast<const char *>(framebuffer), sizeof(Pixel) * SIZE * SIZE);
    resultFile.close();

    std::cout << "Done." << std::endl;
    delete[] framebuffer;
    return EXIT_SUCCESS;
}


