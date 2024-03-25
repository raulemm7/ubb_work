# functii interactiune cu utilizator
def menu():
    print("1) Adaugă număr complex la sfârșitul listei")
    print("2) Inserare număr complex pe o poziție dată")
    print("3) Șterge element de pe o poziție dată")
    print("4) Șterge elementele de pe un interval de poziții.")
    print("5) Înlocuiește toate aparițiile unui număr complex cu un alt număr complex.")
    print("6) Tipărește partea imaginara pentru numerele din listă. (se da intervalul de pozitii)")
    print("7) Tipărește toate numerele complexe care au modulul mai mic decât 10")
    print("8) Tipărește toate numerele complexe care au modulul egal cu 10")
    print("9) Afișează suma numerelor dintr-o subsecvență dată. (se dă poziția de început și sfârșit)")
    print("10) Afișează produsul numerelor dintr-o subsecvență dată. (se dă poziția de început și sfârșit)")
    print("11) Tipărește lista sortată descrescător după partea imaginară")
    print("12) Elimină din listă numerele complexe la care partea reală este prim")
    print("13) Elimină din listă numerele complexe la care modulul este <, = sau > decât un număr dat")
    print("14) Iesire")


mesaj_eroare = 'Introdu o valoare corecta!'


def citire_numar_real(mesaj_introducere):
    while True:
        try:
            user_input = float(input(mesaj_introducere))
            return user_input
        except ValueError:
            print(mesaj_eroare)


def citire_nr_complex(mesaj_info):
    print(mesaj_info)
    parte_reala = citire_numar_real('Introdu partea reala a numarului: ')
    parte_imaginara = citire_numar_real('Introdu partea imaginara a numarului: ')

    return parte_reala, parte_imaginara


def citire_index_valid(lungime_lista, index_minim, mesaj_introducere):
    while True:
        try:
            user_input = int(input(mesaj_introducere))
            if index_minim <= user_input < lungime_lista:
                return user_input

            print(mesaj_eroare)
        except ValueError:
            print(mesaj_eroare)


def citire_comanda():
    while True:
        try:
            user_input = int(input('Introdu o comanda: '))
            if 1 <= user_input <= 14:
                return user_input

            print('Introdu o comanda corecta!')
        except ValueError:
            print('Introdu o comanda corecta!')


def citire_comparatie():
    while True:
        try:
            user_input = input('Introdu un criteriu de comparatie: ')
            if user_input == '=' or user_input == '<' or user_input == '>':
                return user_input

            print('Introdu un criteriu de comparatie corect!')
        except ValueError:
            print('Introdu un criteriu de comparatie corect!')


def tipareste_nr_complex(nr_complex):
    """
    :param nr_complex: lista cu 2 numere reale reprezentand partea reala si partea imaginara
                       a unui numar complex
    """
    if nr_complex[1] >= 0:
        print(nr_complex[0], end="+")
    else:
        print(nr_complex[0], end="")

    print(nr_complex[1], end="i\n")


def tipareste_lista(lista_cu_nr_complexe):
    for i in lista_cu_nr_complexe:
        tipareste_nr_complex(i)


def tipareste_mesaj_informare(mesaj):
    print(mesaj)
