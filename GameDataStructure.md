# LudoNDS Spieldaten Struktur

Dies Beinhaltet eine Dokumentation zur Spieldaten Struktur von LudoNDS.

Die Spieldaten Datei kann im Unter-Menü mit `Spiel Speichern` in `sd:/_nds_/LudoNDS/GameData.dat` gefunden werden. Das Laden funktioniert ebenfalls mit `Spiel Laden` falls diese Datei verfügbar ist.

<details>
	<summary>Version 0.1.0</summary>

## Kompatibilität
Diese Version der Spieldaten ist kompatibel mit:
```
- Ludo3DS v0.4.0
- LudoJS v0.3.0
```

## Figuren Struktur

| Offset    | DataType | Size | Content                               |
| --------- | -------- | ---- | ------------------------------------- |
| 0x0 - 0x1 | uint8_t  | 0x2  | Figuren-Größe                         |
|           |          |      |                                       |
| 0x0 - 0x0 | uint8_t  | 0x1  | Position der Figur ( 0 - 44 )         |
| 0x1 - 0x1 | Boolean  | 0x1  | Ob bereits am Ziel (1) oder nicht (0) |

## Spieler Struktur

| Offset    | DataType        | Size | Content       |
| --------- | --------------- | ---- | ------------- |
| 0x0 - 0x7 | uint8_t         | 0x8  | Spieler-Größe |
|           |                 |      |               |
| 0x0 - 0x1 | Figur_Struktur  | 0x2  | Figur 1       |
| 0x2 - 0x3 | Figur_Struktur  | 0x2  | Figur 2       |
| 0x4 - 0x5 | Figur_Struktur  | 0x2  | Figur 3       |
| 0x6 - 0x7 | Figur_Struktur  | 0x2  | Figur 4       |

## Spiel Struktur

| Offset      | DataType         | Size | Content                                                           |
| ----------- | ---------------- | ---- | ----------------------------------------------------------------- |
| 0x0 - 0x24  | uint8_t          | 0x25 | Spiel-Größe (37 byte)                                             |
|             |                  |      |                                                                   |
| 0x0 - 0x0   | uint8_t          | 0x1  | Aktueller Spieler (0 - 3)                                         |
| 0x1 - 0x1   | uint8_t          | 0x1  | Spieler Anzahl (2 - 4)                                            |
| 0x2 - 0x2   | uint8_t          | 0x1  | Figuren Anzahl (1 - 4)                                            |
| 0x3 - 0xA   | Spieler_Struktur | 0x8  | Spieler 1                                                         |
| 0xB - 0x12  | Spieler_Struktur | 0x8  | Spieler 2                                                         |
| 0x13 - 0x1A | Spieler_Struktur | 0x8  | Spieler 3                                                         |
| 0x1B - 0x22 | Spieler_Struktur | 0x8  | Spieler 4                                                         |
| 0x23 - 0x23 | uint8_t          | 0x1  | Die Anzahl der eingestellten Würfelwürfe (1 / 3)                  |
| 0x24 - 0x24 | uint8_t          | 0x1  | Die Anzahl der Verbleibenden Würfelwürfe                          |
</details>