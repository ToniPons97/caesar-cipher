#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Flags {
    const char encrypt[3];
    const char decrypt[3];
};

void process_text(char* buff, char* text, const short shift, const short size, struct Flags* flags, char* selected_flag);

int main(int argc, char* argv[]) {
    struct Flags flags = { .encrypt = "-e", .decrypt = "-d" };

    char* buff = NULL;
    short shift = abs(atoi(argv[2]));
    const short characters_size = 26;
    
    if (argc != 4) {
        printf("Example usage: %s -d 16 \"Shofjewhqfxo yi vkd\"\n", argv[0]);
        return 1;
    }

    if (strncmp(argv[1], flags.encrypt, 3) && strncmp(argv[1], flags.decrypt, 3)) {
        printf("[!] Invalid flag: Should either be -e or -d.\n");
        return 1;
    }

    buff = (char*) calloc(strlen(argv[3]) + 1, sizeof(char));

    if (buff == NULL) {
        printf("[-] Fatal error: Could not allocate memory. Exiting program.\n");
        return 1;
    }

    process_text(buff, argv[3], shift, characters_size, &flags, argv[1]);

    printf("\nInput: %s\n", argv[3]);
    printf("Output: %s\n\n", buff);

    free(buff);
    return 0;
}

void process_text(char* buff, char* text, const short shift, const short size, struct Flags* flags, char* selected_flag) {
    char* p_start = text;
    char current_char;
    char base;

    while (*p_start) {
        if (isalpha(*p_start)) {
            base = isupper(*p_start) ? 'A' : 'a';

            if (strncmp(selected_flag, flags->encrypt, 3) == 0)
                current_char = ((*p_start - base) + shift) % size + base;
            else if (strncmp(selected_flag, flags->decrypt, 3) == 0)
                current_char = (*p_start -  base - shift + size) % size + base;
            else
                return;

            *buff++ = current_char;
        } else if (isspace(*p_start)) {
            *buff++ = '\x20';
        }

        p_start++;
    }

    *buff = '\0';
}