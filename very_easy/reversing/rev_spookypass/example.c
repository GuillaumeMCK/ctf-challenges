#include <stdio.h>
#include <string.h>

unsigned long parts[26] = {
    0x48, 0x54, 0x42, 0x7b, 0x75, 0x6e, 0x30, 0x62, 0x66, 0x75, 0x35, 0x63, 0x34, 0x74, 0x33, 0x64, 0x5f, 0x35, 0x74, 0x72, 0x31, 0x6e, 0x67, 0x35, 0x7d
};

int main() {
    for (int i = 0; i < 26; i++) {
        putchar(parts[i]);
    }
    return 0;
}
