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

*Tematika*
Pagrindinis veikėjas, Algis, pabunda tamsios girios gilumose, neturėdamas žalio supratimo, kaip jis čia atsidūrė. Netrukus paaiškėja, jog miškas kupinas pavojų, tad pagrindinis Algio prioritetas yra pasipriešinti jiems ir išlikti gyvam.

*Žaidimo idėjos įgyvendinimas*
Žaidimas vyksta 2d aplinkoje iš "top-down" perspektyvos. Grafiniai elementai kurti komandos narių "pixel art" principu, daugiausia 16x16 pikselių laukuose. Žaidėjas turi galimybę vaikščioti, atakuoti, sąveikauti su aplinka ir joje aptinkamais objektais. Žaidimo eigoje sutinkami priešai, trukdantys pasiekti tikslą ir keliantys pastovia grėsmę žaidėjui. Šiurpiai atmosferai užtikrinti, žaidimo eigoje gros pačių kurtas garso takelis.
