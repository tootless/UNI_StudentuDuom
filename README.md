
# StudentuDuom - studentu duomenu apdorojimo aplikacija

# Aprasas

# Instaliavimas / paleidimas 

## Programos Kompiliavimas

### Reikalavimai
- CMake (versija 3.10 arba naujesne)
- C++17 palaikantis kompiliatorius (g++, clang++ arba MSVC)

### Kompiliavimo zingsniai

# Sukuriame build folder
mkdir build

cd build

# Konfiguruoti
cmake ..

# Kompiliuoti
cmake --build .

# Paleisti (Linux/macOS)
./bin/student_program

# Paleisti (Windows OS)
# .\bin\Debug\student_program.exe



# Testavimas - v0.2

Tyrimas buvo atliktas su Visual Studio 2022 /O2 optimizacijos nustatymais.  
Tyrimo 1 failai buvo istrinti pries kiekviena bandyma.  
Testavimo metu testavimo sistemoje nebuvo ijungtos jokios kitos programos.

## Tyrimas 1

### 1. Anksciau sugeneruotu failu nuskaitymas:

|    |  1000  | 100000 | 1000000 |
|:--:|:------:|:-----:|:------:|
| 1. | 0.0478s | 0.619s |  2.965s |
| 2. | 0.0489s | 0.616s |  2.894s |
| 3. | 0.0478s | 0.647s | 2.983s |
| 4. | 0.0479s | 0.593s |  2.979s |
| 5. | 0.0498s | 0.640s |  2.966s|
| Vid. | 0.04844s | 0.623s |  2.9574s |

# Testavimas - v0.4

Tyrimai buvo atlikti su Visual Studio 2022 /O2 optimizacijos nustatymais.  
Tyrimo 1 ir tyrimo 2 failai buvo istrinti pries kiekviena bandyma, isskyrus tyrimo 2 failus, su kuriais buvo testuojamas skaitymo greitis (Tyrimas 2.1).  
Testavimo metu testavimo sistemoje nebuvo ijungtos jokios kitos programos.

## Tyrimas 1

### 1. Failu generavimas ir uzdarymas:

|    |  1000  | 10000 | 100000 | 1000000 | 10000000 |
|:--:|:------:|:-----:|:------:|:-------:|:--------:|
| 1. | 0.003s | 0.03s |  0.31s |  3.29s  |   31.4s  |
| 2. | 0.004s | 0.03s |  0.34s |  3.36s  |  31.9s  |
| 3. | 0.004s | 0.03s |  0.34s |   3.3s  |  31.5s  |
| 4. | 0.003s | 0.04s |  0.35s |  3.32s  |   31.7s  |
| Vid. | 0.0035s | 0.0325s |  0.335s |  3.318s  |   31.625s  |

### Tyrimo 1 output ekrane:

!["test1_1.png"](/Assets/test1_1.png)  
---
Kitas nuotraukas galima rasti repozitorijos assets aplanke (v0.4/Assets/...).

## Tyrimas 2

### 1. Duomenu nuskaitymas is anksciau sugeneruotu failu:

|    |  1000  | 10000 | 100000 | 1000000 | 10000000 |
|:--:|:------:|:-----:|:------:|:-------:|:--------:|
| 1. | 0.005s | 0.04s |  0.46s |  4.62s  |   47.37s  |
| 2. | 0.007s | 0.04s |  0.47s |  4.78s  |   47.66s  |
| 3. | 0.005s | 0.05s |  0.47s |  4.75s  |   47.72s  |
| 4. | 0.006s | 0.05s |  0.47s |  4.7s  |   47.46s  |
| Vid. | 0.00575s | 0.045s |  0.4675s |  4.7125s  |   47.5525s  |

### 2. Studentu rusiavimas i "gerus" ir "blogus" pagal galutini vidurki (>= 5.0 - geras, kitaip - blogas):

|    |  1000  | 10000 | 100000 | 1000000 | 10000000 |
|:--:|:------:|:-----:|:------:|:-------:|:--------:|
| 1. | 0.0004s | 0.0015s |  0.01s |  0.11s  |   1.25s  |
| 2. | 0.0002s | 0.0013s |  0.009s |  0.11s  |   1.19s  |
| 3. | 0.0003s | 0.006s |  0.01s |  0.11s  |   1.28s  |
| 4. | 0.0003s | 0.0012s |  0.01s |  0.11s  |   1.29s  |
| Vid. | 0.003s | 0.0025s |  0.00975s |  0.11s  |  1.2525s  |

### 3. "Geru" ir "blogu" studentu atitinkamu failu generavimas:

|    |  1000  | 10000 | 100000 | 1000000 | 10000000 |
|:--:|:------:|:-----:|:------:|:-------:|:--------:|
| 1. | 0.004s | 0.03s |  0.3s |  4.03s  |   30.72s  |
| 2. | 0.005s | 0.03s |  0.31s |  3.18s  |   30.97s  |
| 3. | 0.004s | 0.03s |  0.31s |  3.14s  |   31.12s  |
| 4. | 0.004s | 0.03s |  0.32s |  3.1s  |   31.04s  |
| Vid. | 0.017s | 0.03s |  0.31s |  3.3625s  |   30.9625s  |

### 4. Visos programos laikas:

|    |  1000  | 10000 | 100000 | 1000000 | 10000000 |
|:--:|:------:|:-----:|:------:|:-------:|:--------:|
| 1. | 0.026s | 0.09s |  0.78s |  8.83s  |   79.75s  |
| 2. | 0.013s | 0.09s |  0.8s |  8.12s  |   80.25s  |
| 3. | 0.011s | 0.099s |  0.81s |  8.04s  |   80.56s  |
| 4. | 0.011s | 0.088s |  0.81s |  7.95s  |   80.2s  |
| Vid. | 0.01525s | 0.09175s |  0.8s |  8.235s  |   80.19s  |

### Tyrimo 2 output ekrane:

!["test2_1.png"](/Assets/test2_1.png)  
---
Kitas nuotraukas galima rasti repozitorijos assets aplanke (v0.4/Assets/...).


# Testavimas - v1.0 subrelease

Tyrimai buvo atlikti su Visual Studio 2022 /O2 optimizacijos nustatymais.  
Tyrimo 1 failai buvo sukurti viena karta pries bandymu pradzia.  
Testavimo metu testavimo sistemoje nebuvo ijungtos jokios kitos programos.  

## Tyrimas 1 - Aprasas

Atliktas tyrimas su trejais skirtingais STL konteineriais (Vektoriai, Sarasai (list) ir Deque).  
Atlikti 3 bandymai kiekvienam konteineriui ir apskaiciuotas vidurkis, kuris pateikiamas kuo tikslesnis (daugiausia 5 simboliai po kablelio).  

Siame tyrime buvo ismatuota minetu konteineriu sparta, programai:  
1. skaitant duomenis is failo, 
2. rusiuojant duomenis didejimo tvarka pagal galutini vidurki (sort funkcija),
3. skirstant duomenis pagal galutini vidurki, sukuriant du naujus tokio pat tipo konteinerius ir naudojant move() funkcija, kad perkelti duomenis is originalaus konteinerio.

Rezultatai pateikiami sekundemis, suapvalinti (stengiamasi nevirsyti 3 skaitmenu po kablelio, taciau yra labai mazu duomenu).


## Aktualus testavimo sistemos parametrai:

### CPU

**Specification**: 12th Gen Intel Core i7-12650H  
**Core count**: 10  
**Thread count**: 16  
**Hyperthreading**:	Not supported  

### RAM

**Specification**: DDR5-4800 (2400 MHz)  
**Memory slots used**: 2 out of 2  
**Total memory**: 16 GB  

### SSD

**Specification**: NVMe SAMSUNG MZVLQ1T0HBLB-00B00  
**Read/Write speed**: 2300/1350 (MB/s)  
**Total capacity**: 953 GB  

## Tyrimas 1 - Rezultatai

### STD::VECTOR

| Ivesciu sk. | Matavimo rodmuo | Test 1 (s) | Test 2 (s) | Test 3 (s) | Vidurkis (s) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1 000** | Nuskaitymas | 0.005 | 0.0048| 0.0048 | 0.0049 |
| | Rusiavimas (sort) | - | - | - | - |
| | Skirstymas | - | -| - | - |
| | **Viskas** | **-** | **-** | **-** | **-** |
| **10 000** | Nuskaitymas | 0.045| 0.047 | 0.047 | 0.046 |
| | Rusiavimas (sort) | 0.001 | 0.001 | 0.001 | 0.001 |
| | Skirstymas | 0.002 | 0.002 | 0.002 | 0.002 |
| | **Viskas** | **0.048** | **0.05** | **0.05** | **0.05** |
| **100 000** | Nuskaitymas | 0.47 | 0.48 | 0.46 | 0.47 |
| | Rusiavimas (sort) | 0.01 | 0.011| 0.010 | 0.010 |
| | Skirstymas | 0.018 | 0.018 | 0.019 | 0.018 |
| | **Viskas** | **0.50** | **0.51** | **0.49** | **0.50** |
| **1 000 000** | Nuskaitymas | 4.57 | 4.60 | 4.63 | 4.60 |
| | Rusiavimas (sort) | 0.1180 | 0.117 | 0.12 | 0.12 |
| | Skirstymas | 0.19 | 0.19 | 0.19 | 0.19 |
| | **Viskas** | **4.88** | **4.90** | **4.94** | **4.91** |
| **10 000 000** | Nuskaitymas | 46.49 | 46.35 | 46.66 | 46.50 |
| | Rusiavimas (sort) | 1.11 | 1.12 | 1.19 | 1.14 |
| | Skirstymas | 2.28 | 2.45 | 2.38 | 2.37 |
| | **Viskas** | **49.89** | **49.92** | **50.26** | **50.01** |

### STD::LIST

| Ivesciu sk. | Matavimo rodmuo | Test 1 (s) | Test 2 (s) | Test 3 (s) | Vidurkis (s) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1 000** | Nuskaitymas | 0.005 | 0.006 | 0.005 | 0.005 |
| | Rusiavimas (sort) | - | - | - | -|
| | Skirstymas | - | - | - | - |
| | **Viskas** | **0.006** | **0.006** | **0.006** | **0.006** |
| **10 000** | Nuskaitymas | 0.047 | 0.046 | 0.044 | 0.046 |
| | Rusiavimas (sort) | 0.001 | 0.001 | 0.001 | 0.001 |
| | Skirstymas | 0.003 | 0.003 | 0.003 | 0.003 |
| | **Viskas** | **0.051** | **0.051** | **0.048** | **0.050** |
| **100 000** | Nuskaitymas | 0.450 | 0.459 | 0.462 | 0.457 |
| | Rusiavimas (sort) | 0.018 | 0.017 | 0.018 | 0.018 |
| | Skirstymas | 0.037 | 0.033 | 0.034 | 0.034 |
| | **Viskas** | **0.505** | **0.509** | **0.514** | **0.509** |
| **1 000 000** | Nuskaitymas | 4.501 | 4.538 | 4.791 | 4.610 |
| | Rusiavimas (sort) | 0.467 | 0.459 | 0.460 | 0.462 |
| | Skirstymas | 0.410 | 0.413 | 0.410 | 0.411 |
| | **Viskas** | **5.378** | **5.409** | **5.662** | **5.483** |
| **10 000 000** | Nuskaitymas | 47.784 | 45.986 | 46.689 | 46.820 |
| | Rusiavimas (sort) | 8.143 | 8.123 | 8.132 | 8.133 |
| | Skirstymas | 5.014 | 4.936 | 4.968 | 4.973 |
| | **Viskas** | **60.942** | **59.045** | **59.790** | **59.926** |

### STD::DEQUE

| Ivesciu sk. | Matavimo rodmuo | Test 1 (s) | Test 2 (s) | Test 3 (s) | Vidurkis (s) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1 000** | Nuskaitymas | 0.005 | 0.006 | 0.006 | 0.006 |
| | Rusiavimas (sort) | - | - | - | - |
| | Skirstymas | 0.001 | - | - | - |
| | **Viskas** | **0.006** | **0.006** | **0.007** | **0.006** |
| **10 000** | Nuskaitymas | 0.047 | 0.046 | 0.046 | 0.046 |
| | Rusiavimas (sort) | 0.001 | 0.001 | 0.002 | 0.001 |
| | Skirstymas | 0.004 | 0.003 | 0.003 | 0.003 |
| | **Viskas** | **0.052** | **0.050** | **0.051** | **0.051** |
| **100 000** | Nuskaitymas | 0.450 | 0.453 | 0.452 | 0.452 |
| | Rusiavimas (sort) | 0.014 | 0.014 | 0.014 | 0.014 |
| | Skirstymas | 0.024 | 0.024 | 0.024 | 0.024 |
| | **Viskas** | **0.488** | **0.490** | **0.490** | **0.489** |
| **1 000 000** | Nuskaitymas | 4.506 | 4.536 | 4.520 | 4.521 |
| | Rusiavimas (sort) | 0.174 | 0.172 | 0.178 | 0.175 |
| | Skirstymas | 0.235 | 0.240 | 0.245 | 0.240 |
| | **Viskas** | **4.915** | **4.948** | **4.944** | **4.936** |
| **10 000 000** | Nuskaitymas | 45.918 | 45.904 | 48.004 | 46.609 |
| | Rusiavimas (sort) | 1.755 | 1.818 | 1.813 | 1.795 |
| | Skirstymas | 3.309 | 3.179 | 3.211 | 3.233 |
| | **Viskas** | **50.983** | **50.902** | **53.027** | **51.637** |

## Tyrimo 1 rezultatu interpretacija




# Testavimas - v1.0 optimizacija

Tyrimai buvo atlikti su Visual Studio 2022 /O2 optimizacijos nustatymais.  
Tyrimo 2 failai buvo sukurti viena karta pries bandymu pradzia.  
Testavimo metu testavimo sistemoje nebuvo ijungtos jokios kitos programos.  

## Tyrimas 2 - Aprasas

Atliktas tyrimas su trejais skirtingais STL konteineriais (Vektoriai, Sarasai (list) ir Deque).  
Atlikti 3 bandymai kiekvienam konteineriui ir apskaiciuotas spartos vidurkis.  
Kadangi spartos duomenys (skaiciai) buvo gan mazi, nebuvo apvalinta.  

Siame tyrime buvo ismatuota minetu konteineriu sparta, programai skirstant duomenis pagal 4 strategijas:
1. Pirmajame tyrime naudota strategija - studentu konteinerio duomenu isvedimas i du naujus konteinerius naudojant std::move(), tuomet istrinimas tusciu duomenu is originalaus konteinerio;  
2. Studentu konteinerio duomenu isvedimas i du naujus konteinerius naudojant push_back();  
3. Studentu konteinerio duomenu isvedimas i viena nauja ('blogu' studentu) konteineri naudojant std::move() ir tuo pat metu istrinimas is originalaus konteinerio, naudojant iteratorius;
4. 3 strategija, optimizuota naudojant std::stable_partition() ir std::move().


## Tyrimas 2 - Rezultatai




## Tyrimo 2 rezultatu interpretacija




