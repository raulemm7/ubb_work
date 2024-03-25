import random
from DOMAIN.setters import Carti, Clienti
from BUSSINES.service import ServiceLista
from VALIDATOR.validation import Validator


class StringRandom:
    @staticmethod
    def generare_string_random():
        len_cuvant = random.randint(5, 12)
        cuvant = ""

        for i in range(0, len_cuvant):
            stare = random.randint(1, 2)
            litera = 0

            if stare == 1:
                # litera mica
                litera = random.randint(97, 122)
            elif stare == 2:
                # litera mare
                litera = random.randint(65, 90)

            cuvant += chr(litera)

        return cuvant


class CarteRandom:
    def __init__(self):
        pass

    @staticmethod
    def generare_descriere_random():
        descriere = ""

        nr_cuvinte = random.randint(5, 9)

        for i in range(0, nr_cuvinte + 1):
            cuvant = StringRandom.generare_string_random()

            descriere += cuvant
            descriere += " "

        return descriere

    @staticmethod
    def generare_nr_exemplare():
        return random.randint(5, 10)

    @staticmethod
    def generare_titlu(lista_carti):
        while True:
            try:
                titlu = StringRandom.generare_string_random()

                rezultat = Validator.validare_titlu_carte(lista_carti, titlu)
                if rezultat:
                    return titlu
            except ValueError:
                pass

    def creeare_carte(self, id_carte, lista_carti):
        titlu = self.generare_titlu(lista_carti)
        autor = StringRandom.generare_string_random()
        descriere = self.generare_descriere_random()
        nr_exemplare = self.generare_nr_exemplare()

        carte = Carti(id_carte, titlu, autor, descriere, nr_exemplare)

        return carte


class ListaCartiRandom:
    @staticmethod
    def adauga_lista_carti(lista):
        nr_carti = random.randint(5, 10)

        for i in range(0, nr_carti):
            carte = CarteRandom()

            lista.adaugare_in_lista(carte.creeare_carte(lista.get_len_lista(), lista))

        # modific nr de elemente care pot fi inchiriate
        lista = ServiceLista.modificare_nr_exemplare(lista)

        return lista


class ClientRandom:
    def __init__(self):
        pass

    @staticmethod
    def generare_cnp_random():
        cnp = ""

        for i in range(0, 13):
            cifra = random.randint(48, 57)
            cnp += chr(cifra)

        return cnp

    @staticmethod
    def creeare_nume_si_prenume(lista_clienti):
        while True:
            try:
                nume = StringRandom.generare_string_random()
                prenume = StringRandom.generare_string_random()

                if Validator.validare_nume(lista_clienti, nume, prenume):
                    return nume, prenume
            except ValueError:
                pass

    def creeare_client(self, id_client, lista_clienti):
        nume, prenume = self.creeare_nume_si_prenume(lista_clienti)
        cnp = self.generare_cnp_random()
        contor = 0

        client = Clienti(id_client, nume, prenume, cnp, contor)

        return client


class ListaClientiRandom:
    @staticmethod
    def adauga_lista_clienti(lista):
        nr_clienti = random.randint(4, 10)

        for i in range(0, nr_clienti):
            client = ClientRandom()

            lista.adaugare_in_lista(client.creeare_client(lista.get_len_lista(), lista))

        return lista
