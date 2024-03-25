from VALIDATOR.validare import Vali


class Output:
    @staticmethod
    def menu():
        print('1. Introdu un jucator nou.')
        print('2. Modifica inaltime.')
        print('3. Creeaza echipa')
        print('4. Importa jucatori din fisier')
        print('5. Iesire din aplicatie')

    @staticmethod
    def print_mesage(mesaj):
        print(mesaj)

    @staticmethod
    def print_echipa(lista):
        print('Prenume     |     Nume     |     Post     |     Inaltime')
        for ent in lista:
            print(ent.get_prenume(), end="      ")
            print(ent.get_nume(), end="      ")
            print(ent.get_post(), end="      ")
            print(ent.get_inaltime(), end="\n")


class Input:
    @staticmethod
    def enter_command(nr_max):
        while True:
            try:
                command = int(input('Introdu o comanda: '))

                if 0 < command <= nr_max:
                    return command

                print('Introdu o comanda corecta!')
            except ValueError:
                print('Introdu o comanda corecta!')

    @staticmethod
    def enter_nume_prenume(lista):
        while True:
            nume = input('Introdu numele jucatorului pe care vrei sa il adaugi: ')
            prenume = input('Introdu prenumele jucatorului pe care vrei sa il adaugi: ')

            rezultat, mesaj = Vali.valideaza_nume_prenume(lista, nume, prenume)

            if rezultat:
                return nume, prenume
            else:
                print(mesaj)

    @staticmethod
    def enter_post():
        while True:
            post = input('Introdu postul jucatorului: ')

            if post in ['Fundas', 'Extrema', 'Pivot']:
                return post

            print('Pozitia unui jucator poate fi doar Fundas, Extrema sau Pivot')

    @staticmethod
    def enter_inaltime():
        while True:
            try:
                inaltime = int(input('Introdu inaltimea jucatorului: '))

                if inaltime > 140:
                    return inaltime

                print('Introdu un numar intreg > 140')
            except ValueError:
                print('Introdu o valoare corecta! (numar intreg > 140)')

    @staticmethod
    def enter_delta_inaltime(minim):
        while True:
            try:
                numar = int(input('Introdu numarul cu care vrei sa modifici inaltime jucatorilor: '))

                if numar < 0 and abs(numar) < minim - 140:
                    return numar
                if numar >= 0:
                    return numar

                print('Introdu o valoarea astfel incat inaltimea tuturor jucatorilor sa ramana > 140!')
            except ValueError:
                print('Introdu o valoare corecta! (numar intreg)')

    @staticmethod
    def enter_file_name():
        while True:
            fisier = input('Introdu numele fisierului: ')

            if '.txt' in fisier:
                return fisier
            print('Introdu un nume de fisier care sa contina extensia ".txt"')
