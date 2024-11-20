% submultime(L: lista, R: lista)
% predicat pentru a genera toate submultimile unei liste
% model de flux: (i, o), (i, i)
% L: lista data
% R: lista in care se va construi submultimea primei liste
submultime([], []).
submultime([H|T], [H|SubT]) :-
    submultime(T, SubT).
submultime([_|T], SubT) :-
    submultime(T, SubT).

% este_munte(L: lista)
% predicat pentru a verifica daca o lista cu cel 
% putin 3 elementeare aspect de munte
% model de flux: (i)
% L: lista ce urmeaza a fi verificata
este_munte([H1, H2, H3|T]) :-
    split_munte([H1, H2, H3|T], Cresc, Desc),
    este_crescatoare(Cresc),
    este_descrescatoare(Desc),
    Cresc \= [],
    Cresc \= [_],
    Desc \= [].

% split_munte(L: lista, C: lista, D: lista)
% predicat pentru a imparti o lista intr-o secventa crescatoare si una descrescatoare
% model de flux: (i, o, o), (i, i, i)
% prima lista: lista cu toate elementele
% Cresc: lista doar cu subsirul crescator de elemente din prima lista
% Descresc: lista cu elementele ramase in prima lista dupa aflarea
% sirului crescator
% L: lista care se va imparti in 2 subliste
% C: lista cu partea crescatoare a listei L, care incepe cu primul element
% D: lista cu partea descrescatoare a listei L, care incepe dupa terminarea celei crescatoare
split_munte([X, Y | T], [X], [Y | T]) :- X > Y.
split_munte([X, Y | T], [X | Cresc], Desc) :-
    X < Y,
    split_munte([Y | T], Cresc, Desc).

% este_crescatoare(L: lista)
% predicat pentru a verifica daca o lista este crescatoare
% model de flux: (i)
% L: o lista cu elemente
este_crescatoare([]).
este_crescatoare([_]).
este_crescatoare([X, Y | T]) :-
    X < Y,
    este_crescatoare([Y | T]).

% este_descrescatoare(L: lista)
% predicat pentru a verifica daca o lista este descrescatoare
% model de flux: (i)
% L: lista cu elemente
este_descrescatoare([]).
este_descrescatoare([_]).
este_descrescatoare([X, Y | T]) :-
    X > Y,
    este_descrescatoare([Y | T]).

% afiseaza_submultimi_munte(L: lista)
% predicat principal pentru a afisa toate submultimile cu aspect de munte
% model de flux: (i)
% L: o lista cu numere intregi distincte pentru care se va cauta
% toate submultimile cu aspect de munte
afiseaza_submultimi_munte(Lista) :-
    submultime(Lista, Sublista),
    este_munte(Sublista),
    write(Sublista), nl,
    fail.
