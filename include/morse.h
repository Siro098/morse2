/**
* @file morse.h
 * @brief Schnittstelle für Morse-Kodierung und -Dekodierung.
 *
 * Dieses Header-File definiert die Funktionen zur Umwandlung von Text in Morsecode
 * sowie zur Rückumwandlung von Morsecode in lesbaren Text. Zusätzlich enthält es
 * Dienstfunktionen zur Anzeige von Hilfe und Entwicklerinformationen.
 *
 * @author Simon Liebl
 * @date 2025
 */

#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Gibt einen Hilfe-Text zur Nutzung des Programms auf der Konsole aus.
     *
     * Diese Funktion beschreibt die unterstützten Kommandozeilenoptionen
     * und deren Verwendung.
     */
    void print_help(void);

    /**
     * @brief Gibt Informationen über den Entwickler im JSON-Format aus.
     *
     * Diese Informationen beinhalten Name, Studiengang und Kontakt.
     */
    void print_programmer_info(void);

    /**
     * @brief Kodiert einen Text in Morsecode.
     *
     * Diese Funktion wandelt den Eingabetext in Morsecode um und schreibt das Ergebnis
     * in den angegebenen Ausgabestrom.
     *
     * @param input Nullterminierter Eingabetext (UTF-8, nur A–Z, 0–9, gängige Satzzeichen).
     * @param output Zielstream (z. B. stdout oder eine geöffnete Datei).
     * @param use_slash_wordspacer true → Wortabstände mit '/' statt drei Leerzeichen.
     * @return 0 bei Erfolg, 1 bei Fehler.
     */
    int encode(const char *input, FILE *output, int use_slash_wordspacer);

    /**
     * @brief Dekodiert eine Morsecode-Zeichenkette in Text.
     *
     * Diese Funktion verarbeitet einen String mit Morsecode (Trennzeichen: Leerzeichen)
     * und schreibt das dekodierte Ergebnis in den angegebenen Stream.
     *
     * @param input Nullterminierter Morsecode-String (z. B. ".- -... / -.-.").
     * @param output Zielstream für dekodierten Text.
     * @return 0 bei Erfolg, 1 bei Fehler.
     */
    int decode(const char *input, FILE *output);

#ifdef __cplusplus
}
#endif

#endif // MORSE_H
