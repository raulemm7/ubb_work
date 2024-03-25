from DOMAIN.setters import Carti, Clienti
from VALIDATOR.validation import Validator


class UIoutput:
    @staticmethod
    def meniu():
        print('Alege o comanda: ')
        print('1. Adauga')  # iteratia 1
        print('2. Sterge')  # iteratia 1
        print('3. Modifica')  # iteratia 1
        print('4. Cauta')  # iteratia 2
        print('5. Inchiriaza/Returneaza carte')  # iteratia 2
        print('6. Rapoarte')  # iteratia 3
        print('7. Afiseaza informatii')  # iteratia 1
        print('8. Iesire')  # iteratia 1
        print('9. Introdu date random')     # lab 8
        print('10. Operatii cu fisier')

    @staticmethod
    def meniu_adauga():
        print('1. Adauga carte')
        print('2. Adauga client')

    @staticmethod
    def meniu_sterge():
        print('1. Sterge carte')
        print('2. Sterge client')

    @staticmethod
    def meniu_modifica():
        print('1. Modifica carte')
        print('2. Modifica client')

    @staticmethod
    def meniu_modifica_carti():
        print('1. Modifica titlul cartii')
        print('2. Modifica autorul cartii')
        print('3. Modifica descrierea cartii')

    @staticmethod
    def meniu_modifica_clienti():
        print('1. Modifica numele clientului')
        print('2. Modifica prenumele clientului')
        print('3. Modifica CNP-ul clientului')

    @staticmethod
    def meniu_cauta():
        print('1. Cauta carte')
        print('2. Cauta clienti')

    @staticmethod
    def meniu_cauta_carte():
        print('1. Cauta carte dupa titlu')
        print('2. Cauta carte dupa autor')

    @staticmethod
    def meniu_cauta_client():
        print('1. Cauta client dupa nume')
        print('2. Cauta client dupa prenume')

    @staticmethod
    def meniu_inc_ret_carte():
        print('1. Inchiriaza carte')
        print('2. Returneaza carte')

    @staticmethod
    def meniu_rapoarte():
        print('1. Cea mai inchiriata carte')
        print('2. Clienti cu carti inchiriate ordonat dupa nume')
        print('3. Primi 20% dintre cei mai activi clienți')

    @staticmethod
    def meniu_afisare_informatii():
        print('1. Afiseaza carti')
        print('2. Afiseaza clienti')

    @staticmethod
    def meniu_random():
        print('1. Introdu date random carti')
        print('2. Introdu date random clienti')

    @staticmethod
    def meniu_operatii_fisier():
        print('1. Introdu date din fisier')
        print('2. Salveaza datele in fisier')
        print('3. Sterge datele din fisier')

    @staticmethod
    def alege_fisier():
        print('1. Fisier carti')
        print('2. Fisier clienti')

    @staticmethod
    def tipareste_mesaj(mesaj):
        print(mesaj)

    @staticmethod
    def afiseaza_informatii_carte(carte):
        print("ID carte: ", carte.get_id())
        print("Titlu: ", carte.get_titlu())
        print("Autor: ", carte.get_autor())
        print("Descriere: ", carte.get_descriere())
        print("Nr. de exemplare inchiriate: ", carte.get_nr_inchirieri())

    @staticmethod
    def afiseaza_informatii_client(client):
        print("ID client: ", client.get_id())
        print("Nume client: ", client.get_nume())
        print("Prenume client: ", client.get_prenume())
        print("CNP client: ", client.get_cnp())
        print("Nr. carti inchiriate: ", client.get_nr_inchirieri())

    class OutputClienti:
        @staticmethod
        def afisare_carti_client(client):
            lista = client.get_carti_inchiriate()

            print(client.get_nume(), client.get_prenume(), ": ", end=" ")

            for i in range(0, len(lista)):
                print(i, lista[i], end=" | ")

            print('\n')


class UIinput:
    @staticmethod
    def citire_comanda(nr_optiuni_valabile):
        while True:
            try:
                user_input = int(input('Introdu o comanda: '))

                if 0 < user_input <= nr_optiuni_valabile:
                    return user_input

                UIoutput.tipareste_mesaj('Introdu o optiune valabila!')

            except ValueError:
                UIoutput.tipareste_mesaj('Introdu o optiune valabila!')

    @staticmethod
    def citire_id(nr_max, mesaj_1, mesaj_2):
        while True:
            try:
                id_obj = int(input('Introdu id-ul ' + mesaj_1 + ' pe care doresti sa ' + mesaj_2))

                if 0 <= id_obj <= nr_max:
                    return id_obj

                UIoutput.tipareste_mesaj('Introdu un id corect! (De la 0 la ' + str(nr_max) + ')')

            except ValueError:
                UIoutput.tipareste_mesaj('Introdu un id corect! (De la 0 la ' + str(nr_max) + ')')

    class InputCarte:
        # citire date carti
        @staticmethod
        def citire_titlu_carte(lista_carti):
            while True:
                try:
                    titlu = input('Introdu titlul cartii: ')

                    rezultat = Validator.validare_titlu_carte(lista_carti, titlu)
                    if rezultat:
                        return titlu

                    UIoutput.tipareste_mesaj('Aceasta carte este deja inregistrata! Introdu alta carte!')
                except ValueError:
                    UIoutput.tipareste_mesaj('Aceasta carte este deja inregistrata! Introdu alta carte!')

        @staticmethod
        def citire_autor_carte():
            autor = input('Introdu autorul cartii: ')
            return autor

        @staticmethod
        def citire_descriere_carte():
            descriere = input('Introdu o scurta descriere a cartii: ')
            return descriere

        @staticmethod
        def citire_nr_exemplare():
            while True:
                try:
                    nr_exemplare = int(input('Introdu numarul de exemplare disponibile pentru aceasta carte: '))
                    if nr_exemplare > 0:
                        return nr_exemplare

                    UIoutput.tipareste_mesaj('Introdu un numar corect de exemplare!')
                except ValueError:
                    UIoutput.tipareste_mesaj('Introdu un numar corect de exemplare!')

        def creeare_carte(self, id_carte, lista_carti):
            titlu = self.citire_titlu_carte(lista_carti)
            autor = self.citire_autor_carte()
            descriere = self.citire_descriere_carte()
            contor = self.citire_nr_exemplare()

            carte = Carti(id_carte, titlu, autor, descriere, contor)

            return carte

        @staticmethod
        def citire_id_carte_inchiriere(id_max, lista_carti):
            while True:
                try:
                    id_carte = UIinput.citire_id(id_max, 'cartii', 'o inchiriezi: ')

                    for i in range(0, lista_carti.get_len_lista()):
                        el = lista_carti.get_el_by_id(i)

                        if el.get_id() == id_carte:
                            if el.get_nr_inchirieri() > 0:
                                return id_carte

                    UIoutput.tipareste_mesaj('Introdu un id de carte pentru care inca se mai '
                                             'gasesc exemplare in biblioteca!')

                except ValueError:
                    UIoutput.tipareste_mesaj('Introdu un id de carte corect!')

        @staticmethod
        def citire_id_carte_returnare(client):
            id_max = client.get_nr_inchirieri() - 1
            lista_carti = client.get_carti_inchiriate()
            while True:
                try:

                    id_carte = UIinput.citire_id(id_max, 'cartii', 'o returnezi: ')

                    if 0 <= id_carte <= id_max:
                        titlu = lista_carti[id_carte]     # returneaza titlu cartii

                        # sterg cartea din lista de carti inchiriate a clientului
                        client.sterge_carte_returnata(titlu)

                        # returnez titlul
                        return titlu

                    UIoutput.tipareste_mesaj('Introdu un id de carte care poate fi returnat!')
                except ValueError:
                    UIoutput.tipareste_mesaj('Introdu un id de carte corect!')

    class InputClient:
        # citire date client
        @staticmethod
        def citire_nume_client():
            nume = input('Introdu numele clientului: ')
            return nume

        @staticmethod
        def citire_prenume_client():
            prenume = input('Introdu prenumele clientului: ')
            return prenume

        @staticmethod
        def nume_si_prenume(lista_clienti):
            while True:
                try:
                    nume = UIinput.InputClient.citire_nume_client()
                    prenume = UIinput.InputClient.citire_prenume_client()

                    rezultat = Validator.validare_nume(lista_clienti, nume, prenume)
                    if rezultat:
                        return nume, prenume

                    UIoutput.tipareste_mesaj('Acest client exista deja inregistrat!')
                except ValueError:
                    UIoutput.tipareste_mesaj('Acest client exista deja inregistrat!')

        @staticmethod
        def citire_cnp_client():
            while True:
                try:
                    cnp = input('Introdu CNP-ul clientului: ')

                    if cnp.isnumeric() and len(cnp) == 13:
                        return cnp

                    UIoutput.tipareste_mesaj('Introdu un CNP corect!')

                except ValueError:
                    UIoutput.tipareste_mesaj('Introdu un CNP corect!')

        def creeare_client(self, id_client, lista_clienti):
            nume, prenume = self.nume_si_prenume(lista_clienti)
            cnp = self.citire_cnp_client()
            contor = 0

            client = Clienti(id_client, nume, prenume, cnp, contor)

            return client

        @staticmethod
        def citire_id_client_inchiriaza(id_max, lista_clienti, titlu_carte):
            while True:
                try:
                    id_client = UIinput.citire_id(id_max, 'clientului', 'sa ii inchiriezi cartea: ')

                    for i in range(0, lista_clienti.get_len_lista()):
                        el = lista_clienti.get_el_by_id(i)
                        lista = el.get_carti_inchiriate()

                        ok = True
                        if el.get_id() == id_client:
                            for titlu in lista:
                                if titlu == titlu_carte:
                                    ok = False

                        if ok:
                            return id_client

                    UIoutput.tipareste_mesaj('Introdu un id de client care nu a mai inchiriat aceasta carte!')

                except ValueError:
                    UIoutput.tipareste_mesaj('Introdu un id de client corect!')

        @staticmethod
        def citire_id_client_returneaza(id_max, lista_clienti):
            while True:
                try:
                    id_client = UIinput.citire_id(id_max, 'clientului', 'returneaza cartea')

                    for i in range(0, lista_clienti.get_len_lista()):
                        el = lista_clienti.get_el_by_id(i)
                        contor = el.get_nr_inchirieri()

                        if el.get_id() == id_client:
                            if contor > 0:
                                return el     # returneaza data de tip Client

                    UIoutput.tipareste_mesaj('Introdu un id de client care are carti inchiriate deja!')

                except ValueError:
                    UIoutput.tipareste_mesaj('Introdu un id corect!')
