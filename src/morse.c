/**
 * @file morse.c
 * @brief Enthält die Implementierung der Morse-Kodierung und die MorseMap-Struktur.
 *
 * Dieses Modul bietet Funktionen zur Umwandlung zwischen Klartext und Morsecode
 * sowie Hilfsfunktionen zur Anzeige von Hilfe- und Metadateninformationen.
 */

#include "morse.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @page datenformate Verwendete Datenformate
 *
 * ## MorseMap
 * Diese Struktur dient als Zuordnungstabelle zwischen Klartext-Zeichen und Morsecode.
 * Sie wird verwendet in den Funktionen `encode()` und `decode()`, um Buchstaben und Ziffern
 * als Morsezeichen darzustellen oder zurückzuwandeln.
 *
 * ```c
 * typedef struct {
 *   char character;
 *   const char* morse;
 * } MorseMap;
 * ```
 *
 * - `character`: Zeichen, z. B. 'A', '5', '='
 * - `morse`: Morsezeichenkette, z. B. ".-", ".....", "-...-"
 */

/**
 * @struct MorseMap
 * @brief Repräsentiert ein Zeichen und dessen zugehörige Morsecode-Zeichenkette.
 *
 * Wird intern als statisches Lookup-Array verwendet.
 */
typedef struct {
    char character;      /**< Klartextzeichen (A-Z, 0-9, Symbole) */
    const char *morse;   /**< Morsecode-Darstellung (z. B. ".-") */
} MorseMap;

/**
 * @brief Morsecode-Tabelle für unterstützte Zeichen.
 */
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

/**
 * @brief Anzahl der Einträge in der Morsecode-Tabelle.
 */
#define TABLE_SIZE (sizeof(morse_table) / sizeof(morse_table[0]))

/**
 * @brief Gibt die Hilfetexte zur Programmnutzung aus.
 */
void print_help() {
    printf("Verwendung: morse [OPTIONEN] [DATEI]\n");
    printf("  -e, --encode               Text in Morsecode umwandeln\n");
    printf("  -d, --decode               Morsecode in Text umwandeln\n");
    printf("  -o, --out [DATEI]          Ausgabe in Datei\n");
    printf("  --slash-wordspacer         Verwende / zwischen Wörtern (nur Encode)\n");
    printf("  --programmer-info          Zeigt JSON-Block mit Autorinfo\n");
    printf("  -h, --help                 Hilfe anzeigen\n");
}

/**
 * @brief Gibt JSON-formatierte Informationen zum Autor aus.
 */
void print_programmer_info() {
    printf("{\n");
    printf("  \"firstname\": \"Simon\",\n");
    printf("  \"surname\": \"Liebl\",\n");
    printf("  \"branch_of_study\": \"TIT24\",\n");
    printf("  \"contact\": \"lieblsimon0304@gmail.com\"\n");
    printf("}\n");
}

/**
 * @brief Wandelt ein Zeichen in dessen Morsecode-Darstellung um.
 *
 * @param c Klartext-Zeichen (Großbuchstabe empfohlen)
 * @return Morsecode-Zeichenkette oder "*" bei unbekanntem Zeichen
 */
const char* char_to_morse(char c) {
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        if (morse_table[i].character == c) {
            return morse_table[i].morse;
        }
    }
    return "*";
}

/**
 * @brief Wandelt eine Morsecode-Zeichenkette in ein Klartextzeichen um.
 *
 * @param code Nullterminierte Morse-Zeichenkette
 * @return Entsprechendes Zeichen oder '*' bei Fehler
 */
char morse_to_char(const char *code) {
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        if (strcmp(morse_table[i].morse, code) == 0) {
            return morse_table[i].character;
        }
    }
    return '*';
}

/**
 * @brief Kodiert einen Klartext-String in Morsecode.
 *
 * Die Funktion nutzt die \ref MorseMap zur Umwandlung und gibt das Ergebnis
 * zeilenweise in den angegebenen Ausgabestrom aus.
 *
 * @param input Eingabetext
 * @param output Ziel-Stream (z. B. stdout oder Datei)
 * @param use_slash_wordspacer Wenn true, wird "/" zwischen Wörtern verwendet
 * @return 0 bei Erfolg
 */
int encode(const char *input, FILE *output, int use_slash_wordspacer) {
    int space_count = 0;
    for (size_t i = 0; input[i] != '\0'; ++i) {
        char c = toupper((unsigned char)input[i]);

        if (c == ' ' || c == '\n' || c == '\r') {
            space_count++;
            continue;
        }

        if (space_count > 0) {
            fprintf(output, use_slash_wordspacer ? " / " : "   ");
            space_count = 0;
        }

        const char *morse = char_to_morse(c);
        fprintf(output, "%s ", morse);
    }

    fprintf(output, "\n");
    return 0;
}

/**
 * @brief Dekodiert eine Morsecode-Zeichenkette in Klartext.
 *
 * Drei Leerzeichen oder ein Slash `/` markieren Worttrennungen.
 *
 * @param input Morsecode-Zeichenkette
 * @param output Ziel-Stream (z. B. stdout oder Datei)
 * @return 0 bei Erfolg
 */
int decode(const char *input, FILE *output) {
    char buffer[16] = {0};  /**< Temporärer Puffer für Morsecode-Symbole */
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
