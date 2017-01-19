# Analyse

## Konfiguration

- Laden eines Files zur Erstellung des Rechtecks
- Matrix muss n² sein
- Struktur:
0. Modus: Rechteck erstellen
```
0 -- Modus: Rechteck erstellen 
20 -- Angabe von n -> n*n Matrix wird initialisiert
0 -- 0=schwarz auf weiß, 1=weiß auf schwarz
10 10 15 10 10 15 -- Orts-Randvektoren Rechteck 
-- x y, x y, x y
```
1. Modus: Angabe einzelner Felder
```
2 -- Modus: einzelne Felder angeben
20 -- Angabe von n -> n*n Matrix wird initialisiert
0 -- 0=schwarz auf weiß, 1=weiß auf schwarz
10 10 15 10 15 15 -- einzelne Felder
```
2. Modus: Angabe der kompletten Matrix 
```
3 -- Modus: einzelne Felder angeben
0 0 0 1 -- Matrix 
1 0 0 1
0 1 0 1
1 0 0 1
```