% Cauta elementul maxim dintr-o listă
% [H|T] -> lista in care se face cautarea
% X -> elementul maxim gasit
% modelul de flux: (i, o)
maxim([X], X).                       % caz de baza (lista are doar un elemet -> maximul e acel element), cond de oprire pt recursivitate
maxim([H|T], Max) :-       
    maxim(T, MaxTail),               % mergem recursiv pana la capatul listei
    Max is max(H, MaxTail).          % la intoarcere, actualizam Max in functie de elem curent si Max gasit pana acum

% Elimina toate aparițiile unui element specific
% X -> elementul pentru care se sterg aparitiile
% prima lista -> lista din care se extrag toate elem \= X
% a doua lista -> lista rezultatul, fara sa contina elem X
% modelul de flux: (i, i, o)
elimina_element(_, [], []).          % caz de baza(daca lista e goala, rezultatul e tot o lista goala), cond de oprire pt recursivitate
elimina_element(X, [X|T], L) :-      % daca primul elem din prima lista = X, nu il includem pe X in Lista rezultat
    elimina_element(X, T, L).
elimina_element(X, [H|T], [H|L]) :- 
    X \= H,                          % daca primul elem din prima lista \= X, l includem pe X in Lista rezultat
    elimina_element(X, T, L).

% Elimina toate aparițiile elementului maxim dintr-o listă
% Lista -> lista din care se vor sterge toate ap elem maxim
% Rezultat -> lista in care nu se regaseste nicio ap a elem maxim fin lista Lista
% modelul de flux: (i, o)
elimina_maxim(Lista, Rezultat) :-
    maxim(Lista, Max),
    elimina_element(Max, Lista, Rezultat).
