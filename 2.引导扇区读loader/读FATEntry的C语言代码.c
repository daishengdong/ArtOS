#include <iostream>
using    namespace    std;

unsigned char fat[] = {
    0xF0, 0xFF, 0xFF, 0xFF,
    0x8F, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x09, 0xA0, 0x00, 0xFF,
};

unsigned short GetFatEntry(int ax) {
    ax *= 3;
    int bOdd = ax % 2;
	ax /= 2;

    unsigned short ret = *(unsigned short*)(fat + ax);

    if (bOdd) return ret >> 4;
    else return ret & 0x0FFF;
}

int main(int argc, char *const argv[]) {
    for (int i = 0; i < 10; ++i) {
        cout << i << ": ";
        printf("%#x\n", GetFatEntry(i));
    }

    return 0;
}

