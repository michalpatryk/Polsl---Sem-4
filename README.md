# MUsroda830
Projekt incremental reactor
Gra polegająca na budowaniu systemu energetycznego i jego ulepszaniu. Celem gry byłoby uzyskanie największej liczby pieniędzy. Na ekranie pokazywane byłyby kupione budynki i ich lokalizacja. Możliwe byłoby kupowanie nowych i ulepszanie już istniejących budynków. Cały projekt wykonany będzie za pomocą biblioteki SFML. Sama gra inspirowana jest grą Reactor Incremental. 

## Gra reactor idle/C++
Projekt wykorzystuje w sobie techniki RTTI, wyjątków, wzorców, kontenerów STL, inteligentych wskaźników oraz wątków. Głównym celem projektu jest lepsze poznanie tych właśnie technik.  
"Sercem" całego projektu są dwie klasy: Reactor jako backend oraz Game jako frontend. Jedynym połączeniem klas Game z Reactor występuje poprzez wystartowanie klasy Clock odpowiedzialnej za liczenie czasu w reaktorze, oraz inicjalizację klasy Reactor odpowiednią mapą (tileMap).  
Sama klasa Game jest połączeniem bibliotek TGUI do wyświetlania interfejsu oraz SFML do wyświetlania samej gry. Wykorzystanie TGUI pozwala na oszczędzenie znacznej ilości czasu na programowaniu takich elementów jak textBoxy, przyciski oraz małe etykiety. Klasa Game jest również odpowiedzialna za załadowanie listy części z których korzysta reaktor - części z kolei przechowywane są w pliku parts.json z wykorzystaniem biblioteki https://github.com/nlohmann/json dostępnej pod licencją MIT.  

Klasa Reactor obsługuje wszystkie wartości związane z liczbą pieniędzy oraz energi. Jej głowny algorytm polega na:
1. Sprawdzenie liczby ticków wykonanych przez Clock (który zwiększa te o jeden co np. 200ms)
2. Wykonanie pętli gry tyle razy, ile było ticków, czyli:
    1. Zmianę energi na pieniądze przez sprzedawców
    2. Generację energi przez wszystkie PowerSource oraz wrzucenie HeatSource do tymczasowego wektora heatGeneratorTiles
    3. Iterację przez wektor heatGeneratorTiles i rozprowadzenie energi na częsci sąsiadujące z danym generatorem mocy, lub gdy takich częsci nie ma - zniszczenie generatora ciepła.
    4. Sprawdzenie czy jakaś część się nie przegrzała. Jeżeli tak - zniszenie jej.
