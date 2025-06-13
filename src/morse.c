
#include "morse.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char character;
    const char *morse;
} MorseMap;

static MorseMap morse_table[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
    {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
    {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
    {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."},
    {'9', "----."}, {'.', ".-.-.-"}, {',', "--..--"}, {':', "---..."}, {';', "-.-.-."},
    {'?', "..--.."}, {'=', "-...-"}, {'-', "-....-"}, {'+', ".-.-."}, {'_', "..--.-"},
    {'(', "-.--."}, {')', "-.--.-"}, {'/', "-..-."}, {'@', ".--.-."}
};

#define TABLE_SIZE (sizeof(morse_table) / sizeof(morse_table[0]))

void print_help() {
    printf("Verwendung: morse [OPTIONEN] [DATEI]\n");
    printf("Optionen:\n");
    printf("  -e, --encode               Text in Morsecode umwandeln\n");
    printf("  -d, --decode               Morsecode in Klartext umwandeln\n");
    printf("  -o, --out [DATEI]          Ausgabedatei\n");
    printf("  --programmer-info          Autorinformation im JSON-Format\n");
    printf("  --slash-wordspacer        Fügt / zwischen Wörter ein (nur mit Encode)\n");
    printf("  -h, --help                 Hilfe anzeigen\n");
}

void print_programmer_info() {
    printf("{\n");
    printf("  \"firstname\": \"Simon\",\n");
    printf("  \"surname\": \"Liebl\",\n");
    printf("  \"branch_of_study\": \"TIT24\",\n");
    printf("  \"contact\": \"lieblsimon0304@gmail.com\"\n");
    printf("}\n");
}

const char* char_to_morse(char c) {
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        if (morse_table[i].character == c) {
            return morse_table[i].morse;
        }
    }
    return "*";
}

char morse_to_char(const char *code) {
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        if (strcmp(morse_table[i].morse, code) == 0) {
            return morse_table[i].character;
        }
    }
    return '*';
}

int encode(const char *input, FILE *output, int use_slash_wordspacer) {
    int space_count = 0;
    for (size_t i = 0; input[i] != '\0'; ++i) {
        char c = toupper((unsigned char)input[i]);

        if (c == ' ' || c == '\n' || c == '\r') {
            space_count++;
            continue;
        }

        if (space_count > 0) {
            if (use_slash_wordspacer) {
                fprintf(output, " / ");
            } else if (space_count >= 1) {
                fprintf(output, "   ");
            }
            space_count = 0;
        }

        const char *morse = char_to_morse(c);
        fprintf(output, "%s ", morse);
    }

    fprintf(output, "\n");
    return 0;
}

int decode(const char *input, FILE *output) {
    char buffer[16] = {0};
    int buf_idx = 0;
    int space_count = 0;

    for (size_t i = 0; ; ++i) {
        char c = input[i];

        if (c == '\0' || c == ' ' || c == '\n' || c == '\r') {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                char decoded = morse_to_char(buffer);
                fprintf(output, "%c", decoded);
                buf_idx = 0;
            }

            if (c == ' ') {
                space_count++;
                if (space_count == 3) {
                    fprintf(output, " ");
                    space_count = 0;
                }
            }

            if (c == '\0') break;
        } else {
            buffer[buf_idx++] = c;
            space_count = 0;
        }
    }

    fprintf(output, "\n");
    return 0;
}
