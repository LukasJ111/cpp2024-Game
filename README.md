# NAUJA INFORMACIJA!

Skaidrės: https://docs.google.com/presentation/d/1x6JBxAxy-klwgXVb0iImNz5uJLxGfCz4/edit?usp=drive_link&ouid=102098508887788281444&rtpof=true&sd=true

Installeris (.exe pavidalu): https://drive.google.com/file/d/17yt5I05OzDK-2qiTnBF_Y27TINu6PGSp/view

# Kompiliavimasis ir paleidimas.

Padaryta, jog nereiktų vestis solutiono.

1. Nuklonuoktie repozitoriją.
```sh
git@github.com:LukasJ111/cpp2024-Game.git
```

2. Nuekit į direktoriją į kurią atklonavot projektą.

3. Nuekit į "Algio Nuotykiai" folderį.

4. Sukompiliuokit projektą su **make** (jei naudojat Windows operacinę sistemą gali būt, kad reiks **mingw32-make** ar kažkas panašaus).

5. Pasileiskit žaidimą spausdami ant "game.exe" failo arba per konsolę su 
```sh
./game.exe
```

6. Dabartinė versija yra demo ir patiems buildinant automatiškai bus debug mode (pasileis konsolė backgrounde ir žaidimas neis per visą ekraną).

# C++ Komandinis projektas - Žaidimas

Mes planuojame sukurti žaidimą pagrinde naudojantis SDL2 grafine biblioteka.
Bus palaikomas C++17 standartas.
Darbo procesui įkvėpimą davė [ši prezentacija](https://bigosaur.com/engine.pd).

Svarbiausi pakeitimai kurie liečia žaidimą yra master atšakoje (kai žaidimas bus paruoštas, master šaka taps pagrindinė).

# Komanda ir atsakomybės

Audrius Kralikas - duomenų valdymas, "back-endinės" operacijos
Kipras Gnižinskas - žaidimo grafikos, grafinė sąveika, žaidimo pasakojimo kryptis
Kipras Kazarinas - žaidimo grafikos, dinaminis judėjimas žaidime, žaidimo pasakojimo kryptis
Lukas Jasiulionis - architektas, vaizdo grafikų sąsajų kūrėjas

# Apie patį žaidimą

*Tematika*.
Pagrindinis veikėjas, Algis, pabunda tamsios girios gilumose, neturėdamas žalio supratimo, kaip jis čia atsidūrė. Netrukus paaiškėja, jog miškas kupinas pavojų, tad pagrindinis Algio prioritetas yra pasipriešinti jiems ir išlikti gyvam.

*Žaidimo idėjos įgyvendinimas*.
Žaidimas vyksta 2d aplinkoje iš "top-down" perspektyvos. Grafiniai elementai kurti komandos narių "pixel art" principu, daugiausia 16x16 pikselių laukuose. Žaidėjas turi galimybę vaikščioti, atakuoti, sąveikauti su aplinka ir joje aptinkamais objektais. Žaidimo eigoje sutinkami priešai, trukdantys pasiekti tikslą ir keliantys pastovia grėsmę žaidėjui. Šiurpiai atmosferai užtikrinti, žaidimo eigoje gros pačių kurtas garso takelis.
