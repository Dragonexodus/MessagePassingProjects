# Analyse

## Konfiguration

- Laden eines Files zur Erstellung des Rechtecks
- Struktur:
1. Modus: Rechteck erstellen
```
1 -- Modus: Rechteck erstellen 
20 -- Angabe von n -> n*n Matrix wird initialisiert
0 -- 0=schwarz auf weiß, 1=weiß auf schwarz
10 10 15 10 15 15 10 15 -- Randpunkte Rechteck 
-- x y, x y, x y, x y
-- ersten 4 Werte liefern obere Kante
-- letzten 4 Werte liefern untere Kante
```
2. Modus: angabe einzelner Felder
```
2 -- Modus: einzelne Felder angeben
20 -- Angabe von n -> n*n Matrix wird initialisiert
0 -- 0=schwarz auf weiß, 1=weiß auf schwarz
10 10 15 10 15 15 10 15 -- einzelne Felder
```
3. Modus: angabe der kompletten Matrix 
```
3 -- Modus: einzelne Felder angeben
0 0 0 1 -- Matrix 
1 0 0 1
0 1 0 1
1 0 0 1
```