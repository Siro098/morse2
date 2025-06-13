
/**
 * @file morse.h
 * @brief Schnittstelle für das Morse-Code-Kodieren und -Dekodieren.
 *
 * Dieses Modul stellt Funktionen zur Verfügung, um Text in Morsecode zu kodieren
 * und Morsecode zurück in Text zu dekodieren.
 *
 * @author Simon Liebl
 * @date 2025
 */

#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>

/**
 * @brief Gibt einen Hilfetext zur Nutzung des Programms auf der Konsole aus.
 */
void print_help();

/**
 * @brief Gibt Informationen zum Programmierer im JSON-Format aus.
 */
void print_programmer_info();

/**
 * @brief Kodiert einen Text in Morsecode.
 *
 * @param input Der Eingabetext als Zeichenkette (Null-terminiert).
 * @param output Ziel-Stream für die Ausgabe (z. B. stdout oder Datei).
 * @param use_slash_wordspacer Wenn true, wird / als Worttrenner eingefügt.
 * @return 0 bei Erfolg, 1 bei Fehler.
 */
int encode(const char *input, FILE *output, int use_slash_wordspacer);

/**
 * @brief Dekodiert Morsecode in Großbuchstaben-Text.
 *
 * @param input Die Morsecode-Eingabe als Zeichenkette.
 * @param output Ziel-Stream für die Ausgabe.
 * @return 0 bei Erfolg, 1 bei Fehler.
 */
int decode(const char *input, FILE *output);

#endif // MORSE_H
