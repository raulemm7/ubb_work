% Predicat pentru a gasi maximul dintr-o lista de numere intregi
% maxim(L: lista, M: intreg)
% modelul de flux: (i, o), (i, i)
% L - lista pentru care se cauta elementul maxim
% M - maximul gasit in L
maxim([X], X).
maxim([H|T], Max) :-
    maxim(T, MaxTail),
    Max is max(H, MaxTail).

% Predicat pentru a gasi maximul dintre numerele intregi dintr-o lista eterogena
% maxim_principal(L: lista, M: intreg)
% modelul de flux: (i, o), (i, i)
% L - lista eterogena din care se cauta maximul
% M - maximul gasit dintre elementele intregi din L
maxim_principal([], -inf).
maxim_principal([H|T], Max) :-
    integer(H),
    maxim_principal(T, MaxTail),
    Max is max(H, MaxTail).
maxim_principal([H|T], Max) :-
    is_list(H),
    maxim_principal(T, Max).

% Predicat pentru a inlocui toate aparitiile unui element intr-o lista
% inlocuieste(X: intreg, Y: intreg, L: lista, R: lista)
% modelul de flux: (i, i, i, o), (i, i, i, i)
% X - elementul de inlocuit
% Y - elementul cu care se inlocuieste
% L - lista initiala
% R - lista rezultata dupa inlocuiri
inlocuieste(_, _, [], []).
inlocuieste(X, Y, [X|T], [Y|Rez]) :-
    inlocuieste(X, Y, T, Rez).
inlocuieste(X, Y, [H|T], [H|Rez]) :-
    X \= H,
    inlocuieste(X, Y, T, Rez).

% Predicat pentru a inlocui maximul listei eterogene in fiecare sublista a acesteia
% cu maximul sublistei respective
% proceseaza_subliste(L: lista, M: intreg, R: lista)
% modelul de flux: (i, i, o), (i, i, i)
% L - lista eterogena care contine subliste
% M - maximul principal din lista L
% R - lista rezultata dupa inlocuiri in subliste
proceseaza_subliste([], _, []).
proceseaza_subliste([H|T], MaxPrincipal, [RezLista|RezTail]) :-
    is_list(H),
    maxim(H, MaxLocal),
    inlocuieste(MaxPrincipal, MaxLocal, H, RezLista),
    proceseaza_subliste(T, MaxPrincipal, RezTail).
proceseaza_subliste([H|T], MaxPrincipal, [H|RezTail]) :-
    integer(H),
    proceseaza_subliste(T, MaxPrincipal, RezTail).

% Predicat pentru a inlocui toate aparitiile maximului principal din fiecare
% sublista cu maximul sublistei respective
% inlocuieste_maxim_principal(Lista: lista, Rezultat: lista)
% modelul de flux: (i, o), (i, i)
% Lista - lista eterogena initiala
% Rezultat - lista in care au fost inlocuite aparitiile maximului principal
inlocuieste_maxim_principal(Lista, Rezultat) :-
    maxim_principal(Lista, MaxPrincipal),
    proceseaza_subliste(Lista, MaxPrincipal, Rezultat).
