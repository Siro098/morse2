# Morse-Code-Programm

Dieses Programm ermöglicht die Umwandlung von Text in Morsecode und umgekehrt.  
Es wurde gemäß den Anforderungen des Programmentwurfs **TI24 (Version 1.0)** an der DHBW Ravensburg, Außenstelle Friedrichshafen, entwickelt.
GIT: https://github.com/Siro098/morse2

---

## Projektstruktur

```
morse/
├── CMakeLists.txt        # CMake-Konfigurationsdatei
├── .gitignore            # Git-Ignore-Datei
├── README.md             # Projektdokumentation (diese Datei)
├── include/              # Header-Dateien
│   └── morse.h           # Deklarationen der Morse-Funktionen
├── src/                  # Implementierung
│   ├── main.c            # Hauptprogramm inkl. Optionen
│   └── morse.c           # Morse-Code-Kodierung/Dekodierung
├── build/                # Build-Ordner (wird automatisch erzeugt)
└── doc/                  # Platz für Doxygen-Dokumentation
```

---

## Funktionalität

Das Programm unterstützt folgende Funktionen:

- Umwandlung von Text in Morsecode (`-e`, `--encode`)
- Umwandlung von Morsecode in Text (`-d`, `--decode`)
- Ausgabe in eine Datei (`-o`, `--out`)
- Anzeige von Hilfe (`-h`, `--help`)
- Anzeige von Entwicklerdaten im JSON-Format (`--programmer-info`)
- Optionaler Slash-Worttrenner (`--slash-wordspacer`)

---

## Unterstützte Zeichen

Das Programm verarbeitet:

- **Buchstaben** A–Z, a–z
- **Zahlen** 0–9
- **Satzzeichen** `. , : ; ?`
- **Mathematische Symbole** `= - +`
- **Formatzeichen** `_ ( ) / @`

Unbekannte Zeichen werden durch `*` ersetzt.

---

## Kompilieren (Tutorial)

### Linux / WSL (empfohlen für DHBW-Testumgebung)

1. Öffne ein Terminal (z. B. Ubuntu WSL unter Windows)
2. Navigiere ins Projektverzeichnis:
   ```bash
   cd /mnt/c/Users/DEINNAME/CLionProjects/morse
   ```
3. Installiere einmalig die benötigten Tools:
   ```bash
   sudo apt update
   sudo apt install cmake build-essential
   ```
4. Kompiliere das Programm:
   ```bash
   mkdir -p build
   cd build
   cmake ..
   make
   ./morse --help
   ```

### Windows (CLion)

1. Öffne das Projekt in CLion
2. Stelle sicher, dass das Toolchain-Profil „CMake + MinGW“ oder „WSL“ verwendet
3. Klicke auf **Build Project** ▶ oder nutze das Terminal:
   ```bash
   cmake -B build
   cmake --build build
   ```

---

## Beispielverwendung

```bash
# Text zu Morse
./morse -e "Hallo Welt"

# Morse zu Text
./morse -d ".... .- .-.. .-.. ---   .-- . .-.. -"

# Datei wandeln
./morse -e input.txt -o output.txt

# Worttrenner mit Slash
./morse -e "Hallo Welt" --slash-wordspacer

# Hilfe anzeigen
./morse --help

# Entwicklerinformationen
./morse --programmer-info
```

---

## Anforderungen

Dieses Projekt erfüllt alle **funktionalen (ReqFuncXX)** und **nicht-funktionalen Anforderungen (ReqNonFuncXX)** der Spezifikation, u. a.:

- Verwendung von `getopt_long()` für die Kommandozeilenoptionen
- Volle Unterstützung aller geforderten Zeichensätze
- Korrekte Buchstaben- und Worttrennung (`SPACE`, `SPSPSP`)
- Datei- und Pipe-Ein-/Ausgabe
- Formatkonforme CMake-Struktur
- Optional: Doxygen-Dokumentation aller Funktionen

---

## Autor

```json
{
  "firstname": "Simon",
  "surname": "Liebl",
  "branch_of_study": "TIT24",
  "contact": "lieblsimon0304@gmail.com"
}
```

> Erstellt im Rahmen der Prüfungsleistung TI24 – Programmentwurf C/C++, DHBW Ravensburg – 2025
