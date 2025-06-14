/**
 * @file main.c
 * @brief Hauptprogramm für das Morse-Code-Tool (TI24)
 *
 * Dieses Programm analysiert Kommandozeilenargumente und leitet die Eingabe
 * an die passenden Funktionen zur Morse-Kodierung oder -Dekodierung weiter.
 * Unterstützt Datei- und Pipedaten sowie Umleitungen.
 *
 * Unterstützte Optionen:
 * - `-e`, `--encode`: Text in Morsecode umwandeln
 * - `-d`, `--decode`: Morsecode in Text umwandeln
 * - `-o`, `--out`: Ausgabe in Datei
 * - `--slash-wordspacer`: Fügt `/` als Worttrenner ein (nur bei Encode)
 * - `--programmer-info`: Gibt JSON mit Metadaten aus
 * - `-h`, `--help`: Hilfe anzeigen
 *
 * @author Simon Liebl
 * @date 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "morse.h"

#define BUFFER_SIZE 8192 /**< Puffergröße für Ein-/Ausgabe */

/**
 * @brief Definition der verfügbaren Kommandozeilenoptionen
 */
static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},                 /**< Hilfe anzeigen */
    {"encode", no_argument, 0, 'e'},               /**< Kodierung in Morsecode */
    {"decode", no_argument, 0, 'd'},               /**< Dekodierung aus Morsecode */
    {"out", required_argument, 0, 'o'},            /**< Dateiname für Ausgabe */
    {"programmer-info", no_argument, 0, 0},        /**< Ausgabe der Programmierer-Infos */
    {"slash-wordspacer", no_argument, 0, 1},       /**< `/` als Worttrenner (nur Encode) */
    {0, 0, 0, 0}                                   /**< Abschlussmarkierung */
};

/**
 * @brief Einstiegspunkt des Programms. Verarbeitet Optionen und leitet Daten weiter.
 *
 * Diese Funktion verarbeitet alle Kommandozeilenargumente, lädt entweder eine Datei
 * oder liest von `stdin`, ruft dann die passende Kodierungs-/Dekodierungsfunktion auf
 * und gibt das Ergebnis auf `stdout` oder in eine Datei aus.
 *
 * @param argc Anzahl der Argumente
 * @param argv Argumentvektor
 * @return 0 bei Erfolg, 1 bei Fehler
 */
int main(int argc, char *argv[]) {
    int opt;                          /**< Aktuell verarbeitete Option */
    int encode_flag = 0;              /**< Flag für Kodierung */
    int decode_flag = 0;              /**< Flag für Dekodierung */
    int use_slash_wordspacer = 0;     /**< Flag für '/' als Worttrenner */
    char *output_filename = NULL;     /**< Dateiname für Ausgabe, falls angegeben */

    // Optionen verarbeiten
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
            case 0:  // --programmer-info
                print_programmer_info();
                return 0;
            case 1:  // --slash-wordspacer
                use_slash_wordspacer = 1;
                break;
            case '?':
            default:
                fprintf(stderr, "Unbekannte Option. Verwenden Sie --help für Hilfe.\n");
                return 1;
        }
    }

    // Prüfen auf widersprüchliche Optionen
    if (encode_flag && decode_flag) {
        fprintf(stderr, "Fehler: --encode und --decode dürfen nicht gleichzeitig verwendet werden.\n");
        return 1;
    }

    if (use_slash_wordspacer && !encode_flag) {
        fprintf(stderr, "Fehler: --slash-wordspacer darf nur mit --encode verwendet werden.\n");
        return 1;
    }

    char buffer[BUFFER_SIZE]; /**< Eingabepuffer */
    size_t input_len = 0;     /**< Tatsächlich gelesene Länge */
    buffer[0] = '\0';

    /**
     * @brief Eingabe verarbeiten
     *
     * Wenn ein Dateiname als Argument angegeben ist, wird die Datei gelesen.
     * Andernfalls wird von `stdin` gelesen.
     */
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

    FILE *out = stdout; /**< Standardausgabe als Voreinstellung */
    if (output_filename) {
        out = fopen(output_filename, "w");
        if (!out) {
            fprintf(stderr, "Fehler beim Öffnen der Ausgabedatei: %s\n", output_filename);
            return 1;
        }
    }

    /**
     * @brief Aufruf der jeweiligen Verarbeitungsfunktion
     */
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
