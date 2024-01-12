#include <cstdio>
#include <opencv2/opencv.hpp>
#include <bitset>
#include <cstdlib>

using namespace cv;

int main(int argc, char** argv) {

    if (argc != 3) { printf("usage: shove your computer up your ass\n"); return -1; }

    int arg2 = atoi(argv[2]) - atoi(argv[2]) % 8;
    Mat image = imread(argv[1], 1);

    Mat channels[3];
    split(image, channels);
    Mat fl = channels[0].reshape(1, image.rows * image.cols);

    fl.forEach<uint8_t>([&](uint8_t &f, const int *p) {f %= 2;});

    Rect roi(0, 0, 1, arg2);
    Mat ff = fl(roi).reshape(8, int(arg2 / 8));

    for (int i = 0; i < ff.rows; i++) {
        Vec<uint8_t,8> &f = ff.at<Vec<uint8_t,8>>(i, 0);
        std::bitset<8> bits;
        for(int a=0; a < 8; a++){bits.set(7-a,f[a]);}
        putchar(bits.to_ulong());
    }

    return 0;
}
