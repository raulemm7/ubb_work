% Numarul de aparitii intr o lista al unui element
% [H|T] -> lista in care se face cautarea
% X -> elementul pentru care se face cautarea
% Count -> numarul de aparitii ale lui X in [H|T]
% model de flux: (i, i, o) 
numar_aparitii([], _, 0).             % cazul de baza (lista e goala => Count = 0), conditie de oprire pentru recursivitate
numar_aparitii([H|T], X, Count) :-
    H = X,                            % daca primul elem din lista == elem pt care se face numararea
    numar_aparitii(T, X, Count1),     % apelam recursiv incrementand Count
    Count is Count1 + 1.
numar_aparitii([H|T], X, Count) :- 
    H \= X,                           % daca primul elem din lista != elem pt care se face numararea
    numar_aparitii(T, X, Count).      % continuam cu apelul recursiv

% elimina elementele care se repeta
% [H|T] -> lista din care se vor extrage elementele
% FullList -> lista nemodificata pentru a calcula nr de ap al fiecarui elem din lista
% Result -> Lista rezultata in urma modificarilor
% modelul de flux: (i, i, o)
sterge_repetate([], _, []).                   % cazul de baza (lista e goala -> lista goala), cond de oprire pt recursivitate            
sterge_repetate([H|T], FullList, Result) :-
    numar_aparitii(FullList, H, Count),       % determinam nr de aparitii in lista al primului element
    Count =:= 1,                              % Dacă elementul apare o singură dată, îl păstrăm
    sterge_repetate(T, FullList, RestResult), % continuam recursiv 
    Result = [H|RestResult].                  % adaugam elem cu rezultatul obtinut in urma recursivitatii
sterge_repetate([H|T], FullList, Result) :-
    numar_aparitii(FullList, H, Count),        
    Count > 1,                                % Dacă elementul apare de mai multe ori, îl eliminăm
    sterge_repetate(T, FullList, Result).     % continuam apelul recursiv fara sa modificam rezultatul

% Predicatul principal
% List: o lista de numere pentru care elementele care apar de mai multe ori vor fi sterse
% Result: rezultatul in urma aplicarii multiplelor stergeri asupra listei
% modelul de flux: (i, o)
sterge_duplicate(List, Result) :-
    sterge_repetate(List, List, Result).
