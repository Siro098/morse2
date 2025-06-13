
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "morse.h"

#define BUFFER_SIZE 8192

int main(int argc, char *argv[]) {
    int opt;
    int encode_flag = 0;
    int decode_flag = 0;
    int use_slash_wordspacer = 0;
    char *output_filename = NULL;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"encode", no_argument, 0, 'e'},
        {"decode", no_argument, 0, 'd'},
        {"out", required_argument, 0, 'o'},
        {"programmer-info", no_argument, 0, 0},
        {"slash-wordspacer", no_argument, 0, 1},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hedo:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'e':
                encode_flag = 1;
                break;
            case 'd':
                decode_flag = 1;
                break;
            case 'o':
                output_filename = optarg;
                break;
            case 0:
                print_programmer_info();
                return 0;
            case 1:
                use_slash_wordspacer = 1;
                break;
            case '?':
            default:
                fprintf(stderr, "Unbekannte Option. Verwenden Sie --help für Hilfe.\n");
                return 1;
        }
    }

    if (encode_flag && decode_flag) {
        fprintf(stderr, "Fehler: --encode und --decode dürfen nicht gleichzeitig verwendet werden.\n");
        return 1;
    }

    if (use_slash_wordspacer && !encode_flag) {
        fprintf(stderr, "Fehler: --slash-wordspacer darf nur mit --encode verwendet werden.\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t input_len = 0;
    buffer[0] = '\0';

    if (optind < argc) {
        FILE *f = fopen(argv[optind], "r");
        if (!f) {
            fprintf(stderr, "Fehler beim Öffnen der Datei: %s\n", argv[optind]);
            return 1;
        }
        input_len = fread(buffer, 1, BUFFER_SIZE - 1, f);
        buffer[input_len] = '\0';
        fclose(f);
    } else {
        input_len = fread(buffer, 1, BUFFER_SIZE - 1, stdin);
        buffer[input_len] = '\0';
    }

    FILE *out = stdout;
    if (output_filename) {
        out = fopen(output_filename, "w");
        if (!out) {
            fprintf(stderr, "Fehler beim Öffnen der Ausgabedatei: %s\n", output_filename);
            return 1;
        }
    }

    int result = 0;
    if (decode_flag) {
        result = decode(buffer, out);
    } else {
        result = encode(buffer, out, use_slash_wordspacer);
    }

    if (out != stdout) {
        fclose(out);
    }

    return result;
}
