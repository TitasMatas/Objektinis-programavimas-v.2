# Studentų pažymių valdymo sistema ir spartos analizė

## Aprašymas
Programa skirta:
- Įvesti studentų duomenis (rankiniu būdu, atsitiktinai arba iš failo)
- Apskaičiuoti galutinį pažymį pagal vidurkį ir medianą
- Suskirstyti studentus į dvi kategorijas:
  - **Protingi** (galutinis vidurkis ≥ 5.0)
  - **Ne tokie protingi** (galutinis vidurkis < 5.0)
- Išvesti rezultatus į failus
- Atlikti spartos analizę su skirtingais duomenų kiekiais (List ir Vector strategijos)

## Strategijos
- `Strategija 1` – Paprastas skirstymas į kategorijas naudojant iteracinį erase metodą:
  - Kiekvienas studentas tikrinamas ir perkeltas į atitinkamą vektorių arba sąrašą. 
  - Trūkumas: daug erase operacijų → gali būti O(n²) blogiausiu atveju.
- `Strategija 2` – Optimizuotas skirstymas naudojant std::partition:
  - Vienu perėjimu padalina duomenis į dvi grupes.
  - Naudojamas move ir vienkartinis erase → O(n) laikas.
- `Strategija 3` – Optimaliausias algoritmas (naudojant std::partition_copy arba copy_if):
  - Sukuria dvi atskiras kolekcijas vienu arba dviem perėjimais.
  - Mažiausiai realokacijų, geras našumas dideliems duomenų kiekiams.


## Projekto struktūra
- `main.cpp` – pagrindinė programos logika
- `functions.cpp` – funkcijų realizacija
- `vector.cpp` – funkcijų realizacija naudojant std::vector.
- `functions.h` – funkcijų deklaracijos
- `student.h` – struktūra `Student`
- Testiniai failai:
  - `studentai10.txt`
  - `studentai100.txt`
  - `studentai1000.txt`
  - `studentai10000.txt`
  - `studentai100000.txt`

## Paleidimo instrukcija (su g++)

### Kaip kompiliuoti
- Terminale:
  ```bash
  g++ -std=c++17 main.cpp v.pradine.cpp vector.cpp -o programa.exe
  ```

### Kaip paleisti
- Terminale:
  ```bash
  ./programa.exe
  ```
## idiegimo instrukcija

### Variantas A: Make (Unix/Linux/macOS)
- Įdiek g++ (pvz., `sudo apt install build-essential` arba `xcode-select --install` macOS).
- Terminale:
   ```bash
   make        # sukompiliuoja 'programa'
   make run    # paleidžia ./programa
   make clean  # išvalo build artefaktus
   ```

### Variantas B: CMake (Windows/Linux/macOS)
- Įdiek CMake (https://cmake.org) ir C++ kompiliatorių (MSVC arba MinGW Windows, gcc/clang Linux/macOS).
- Terminale:
  ```bash
  mkdir -p build && cd build
  cmake -DCMAKE_BUILD_TYPE=Release ..
  cmake --build . --config Release
  ```

### Programos paleidimas
- Terminale:
  ```bash
  ./programa                 # Linux/macOS
  .\Release\programa.exe     # Windows (MSVC)
  .\programa.exe             # Windows (MinGW)
  ```


# Programos veikimas pakeistas su Class

## NAUJI Spartos analizės rezultatai

### LIST - 1 strategija

| Failas              | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) |
| ------------------- | --------------- | -------------- | ------------ | ----------- |
| studentai10.txt     | 0.000287        | 0.014530       | 0.005609     | 0.026765    |
| studentai100.txt    | 0.001294        | 0.000061       | 0.007433     | 0.012779    |
| studentai1000.txt   | 0.009958        | 0.000487       | 0.037817     | 0.054260    |
| studentai10000.txt  | 0.071582        | 0.002647       | 0.266534     | 0.343992    |
| studentai100000.txt | 0.793006        | 0.025544       | 3.276945     | 4.102341    |

### LIST - 2 strategija

| Failas              | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) |
| ------------------- | --------------- | -------------- | ------------ | ----------- |
| studentai10.txt     | 0.000304        | 0.000016       | 0.002369     | 0.006527    |
| studentai100.txt    | 0.000784        | 0.000011       | 0.002161     | 0.007033    |
| studentai1000.txt   | 0.006680        | 0.000042       | 0.014642     | 0.024586    |
| studentai10000.txt  | 0.061414        | 0.000526       | 0.141509     | 0.208424    |
| studentai100000.txt | 0.770634        | 0.007333       | 1.824534     | 2.609612    |

### LIST - 3 strategija

| Failas              | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) |
| ------------------- | --------------- | -------------- | ------------ | ----------- |
| studentai10.txt     | 0.000578        | 0.000010       | 0.007253     | 0.034341    |
| studentai100.txt    | 0.003710        | 0.000140       | 0.024040     | 0.148614    |
| studentai1000.txt   | 0.016724        | 0.000519       | 0.063894     | 0.087855    |
| studentai10000.txt  | 0.180881        | 0.006807       | 0.295709     | 0.515608    |
| studentai100000.txt | 1.122824        | 0.042183       | 2.569667     | 3.738944    |

## LIST pokitis pridėjus Class

| Failas              | Pokytis S1 (%) | Pokytis S2 (%) | Pokytis S3 (%) |
| ------------------- | -------------- | -------------- | -------------- |
| studentai10.txt     | +371 %         | −10 %          | +261 %         |
| studentai100.txt    | +85 %          | +12 %          | +1180 %        |
| studentai1000.txt   | +42 %          | −36 %          | +191 %         |
| studentai10000.txt  | +37 %          | −13 %          | +146 %         |
| studentai100000.txt | +52 %          | +7 %           | +107 %         |


### Vector - 1 strategija

| Failas              | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) |
| ------------------- | --------------- | -------------- | ------------ | ----------- |
| studentai10.txt     | 0.000294        | 0.000008       | 0.004795     | 0.016581    |
| studentai100.txt    | 0.000972        | 0.000067       | 0.004673     | 0.010106    |
| studentai1000.txt   | 0.007309        | 0.000207       | 0.028303     | 0.041310    |
| studentai10000.txt  | 0.067681        | 0.001429       | 0.166701     | 0.239431    |
| studentai100000.txt | 0.573965        | 0.008311       | 1.667649     | 2.257191    |

### VECTOR - 2 strategija

| Failas              | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) |
| ------------------- | --------------- | -------------- | ------------ | ----------- |
| studentai10.txt     | 0.000466        | 0.000021       | 0.003100     | 0.010703    |
| studentai100.txt    | 0.001463        | 0.000146       | 0.002706     | 0.010808    |
| studentai1000.txt   | 0.007682        | 0.000347       | 0.015061     | 0.028531    |
| studentai10000.txt  | 0.053238        | 0.001095       | 0.125299     | 0.183045    |
| studentai100000.txt | 0.660618        | 0.020442       | 1.600361     | 2.285500    |

### Vector - 3 strategija

| Failas              | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) |
| ------------------- | --------------- | -------------- | ------------ | ----------- |
| studentai10.txt     | 0.000607        | 0.000010       | 0.003074     | 0.008804    |
| studentai100.txt    | 0.001164        | 0.000037       | 0.003762     | 0.010684    |
| studentai1000.txt   | 0.007718        | 0.000158       | 0.020678     | 0.032670    |
| studentai10000.txt  | 0.065757        | 0.002209       | 0.274454     | 0.358372    |
| studentai100000.txt | 0.832484        | 0.019327       | 1.222532     | 2.082422    |

## Vector pokitis pridėjus Class

| Failas              | Pokytis S1 (%) | Pokytis S2 (%) | Pokytis S3 (%) |
| ------------------- | -------------- | -------------- | -------------- |
| studentai10.txt     | +189 %         | +73 %          | +29 %          |
| studentai100.txt    | +44 %          | +72 %          | −85 %          |
| studentai1000.txt   | +106 %         | +4 %           | −13 %          |
| studentai10000.txt  | +53 %          | +8 %           | +34 %          |
| studentai100000.txt | +37 %          | +58 %          | −32 %          |


## Pastabos
- Po visų atnaujinimų Vector laikas gerokai pamažėjo 1 > 2 > 3, kur su 3 Strategija, jis yra optimaliausias
- Po Class pridėjimo List kompiliacija pasikeitė, naujausi testai parodė, jog optimaliausia strategija tampa 2

## Testavimo sistemos parametrai
| Parametras | Reikšmė |
|------------|---------|
| CPU | 11th Gen Intel(R) Core(TM) i5-1145G7 @ 2.60GHz |
| RAM | 16 GB DDR4 |
| HDD / SSD | NVMe SSD |
| OS | Windows 11 Enterprise x64 |
