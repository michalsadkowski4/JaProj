Repozytorium stworzone celem kontroli wersji podczas pracy nad projektem z przedmiotu Języki Asemblerowe 

Temat projektu: Wyznaczanie otoczki wypukłej w przestrzeni dwuwymiarowej z wykorzystaniem algorytmu Grahama

Opis projektu:

Projekt ten dotyczy zagadnienia z obszaru geometrii obliczeniowej, polegającego na wyznaczeniu
najmniejszej otoczki wypukłej, która obejmuje wszystkie punkty zadanego zbioru w przestrzeni
dwuwymiarowej. Implementacja będzie opierać się na algorytmie Grahama, jednym z powszechnie
stosowanych algorytmów do wyznaczania otoczki wypukłej. Program przyjmie dane wejściowe
w postaci pliku tekstowego (.txt), zawierającego współrzędne punktów w układzie kartezjańskim
(𝑥, 𝑦). W części zaimplementowanej w języku asemblera obliczane będą kąty, jakie tworzą
poszczególne punkty z prostą przechodzącą przez punkt początkowy. Następnie punkty zostaną
posortowane według tych kątów. Dodatkowo w ramach obliczeń zostanie uwzględnione wyznaczenie
iloczynu wektorowego, niezbędnego do poprawnego działania algorytmu. Wyjściem programu będzie
lista współrzędnych punktów tworzących otoczkę wypukłą, zapisana w pliku .txt, z możliwością
graficznej wizualizacji wyników.
Złożoność czasowa zastosowanego algorytmu wynosi 𝑂(𝑛 log 𝑛) gdzie 𝑛 to liczba punktów
w zbiorze wejściowym. Złożoność ta wynika głównie z procesu sortowania punktów, który dominuje
czas wykonania algorytmu.
Projekt ma na celu opracowanie efektywnego rozwiązania problemu otoczki wypukłej dla punktów
w przestrzeni dwuwymiarowej, z zastosowaniem algorytmu Grahama. Kluczowym elementem będzie
optymalizacja części obliczeniowej przy wykorzystaniu asemblera, co pozwoli na zwiększenie
wydajności programu poprzez bezpośrednią manipulację na poziomie sprzętowym.

Autor: Michał Sadkowski sekcja 9 rok 3 Gliwice
