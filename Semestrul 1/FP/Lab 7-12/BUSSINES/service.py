import unittest
from REPOSITORY.storage import StorageInformation
from DOMAIN.setters import Clienti, Carti


class ServiceLista:
    @staticmethod
    def sterge_din_lista(lista, id_element):
        # sterg elementul care are id-ul id_element
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_element:
                lista.stergere_din_lista(el.get_id())
                break

        # actualizez id-urile
        contor = 0
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)
            el.set_id(contor)
            contor += 1

        return lista

    @staticmethod
    def modificare_nr_exemplare(lista):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            nr_carti = el.get_nr_inchirieri()
            lista.set_exemplare_valabile(nr_carti)

        return lista

    @staticmethod
    def copiaza_lista(lista_sursa, lista_destinatie):
        for i in range(0, lista_sursa.get_len_lista()):
            el = lista_sursa.get_el_by_id(i)
            lista_destinatie.adaugare_in_lista(el)


class ServiceCarti:
    @staticmethod
    def modifica_titlu(lista, id_obj, new_titlu):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_obj:
                el.set_titlu(new_titlu)
        return lista

    @staticmethod
    def modifica_autor(lista, id_obj, new_autor):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_obj:
                el.set_autor(new_autor)
        return lista

    @staticmethod
    def modifica_descriere(lista, id_obj, new_descriere):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_obj:
                el.set_descriere(new_descriere)
        return lista

    @staticmethod
    def cauta_dupa_titlu(lista, titlu):
        """
        functie care cauta o carte dupa titlu
        :param lista: lista de carti
        :param titlu: titlul dupa care se cauta cartea
        :return: returneaza cartea (adresa in memorie) al carei titlu este acelasi cu param titlu,
                 0 in cazul in care nu s a gasit nicio carte cu acest titlu

        --COMPLEXITATE--
        O(n), n = nr de elemenete din lista
        Best case: O(1): elementul cu titlul cautat se afla pe prima pozitie in lista
        Worst case: O(n): elementul cu titlul cautat ori se afla pe ultima pozitie, ori nu se gaseste in lista
        Average case: (1 + 2 + .. + n) / n = n(n + 1) / 2n = 1/2 * n => O(n)
        """
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_titlu() == titlu:
                return el   # returnez cartea cautata
        return 0            # 0 inseamna ca nu am gasit cartea si afisez mesaj de eroare in main

    @staticmethod
    def cauta_dupa_autor(lista, autor, id_element):
        """
        functie care cauta o carte dupa autor intr o lista de carti
        -- functie implementata recursiv --
        :param lista: lista de carti
        :param autor: autorul dupa care se face cautarea
        :param id_element: id_ul cartii curente dupa care se face verificarea (pentru implementarea recursiva)
        :return: 0 daca nu s-a gasit o carte care sa aiba acel autor,
                 cartea (adresa in memorie) in caz contrar
        """
        if id_element == lista.get_len_lista():
            return 0
        else:
            el = lista.get_el_by_id(id_element)
            if el.get_autor() == autor:
                return el
            else:
                return ServiceCarti.cauta_dupa_autor(lista, autor, id_element + 1)

    @staticmethod
    def scade_carti_disponibile(lista, id_carte):
        """functie care scade nr de exemplare disponibile pentru cartea ce urmeaza a fi inchiriata"""
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_carte:
                contor = el.get_nr_inchirieri()
                el.set_nr_inchirieri(contor - 1)

                return lista

    @staticmethod
    def adauga_carte_returnata(lista, titlu_carte, id_element):
        """functie care adauga un exemplar la nr de exemplare disponibile pentru cartea ce urmeaza a fi returnata
           -- functie implementata recursiv --
        """
        el = lista.get_el_by_id(id_element)
        if el.get_titlu() == titlu_carte:
            contor = el.get_nr_inchirieri()
            el.set_nr_inchirieri(contor + 1)

            return lista
        else:
            return ServiceCarti.adauga_carte_returnata(lista, titlu_carte, id_element + 1)

    @staticmethod
    def cea_mai_inchiriata_carte(lista):
        """functir care returneaza cartea cea mai inchiriata"""
        carte = lista.get_el_by_id(0)
        nr_max_inchirieri = carte.get_nr_exemplare_inchiriate()

        for i in range(1, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_nr_exemplare_inchiriate() > nr_max_inchirieri:
                nr_max_inchirieri = el.get_nr_exemplare_inchiriate()
                carte = el

        return carte


class TestsCarti(unittest.TestCase):
    def test_modifica_titlu(self):
        lista = StorageInformation()
        carte = Carti(0, 'titlu', 'autor', 'ceva descriere', 23)
        lista.adaugare_in_lista(carte)

        ServiceCarti.modifica_titlu(lista, carte.get_id(), 'ceva_titlu_foarte_nou')

        self.assertEqual(carte.get_titlu(), 'ceva_titlu_foarte_nou')

    def test_modifica_autor(self):
        lista = StorageInformation()
        carte = Carti(0, 'titlu', 'autor', 'ceva descriere', 23)
        lista.adaugare_in_lista(carte)

        ServiceCarti.modifica_autor(lista, carte.get_id(), 'alt autor')

        self.assertEqual(carte.get_autor(), 'alt autor')

    def test_modifica_descriere(self):
        lista = StorageInformation()
        carte = Carti(0, 'titlu', 'autor', 'ceva descriere', 23)
        lista.adaugare_in_lista(carte)

        ServiceCarti.modifica_descriere(lista, carte.get_id(), 'alta descriere')

        assert carte.get_descriere() == 'alta descriere'
        self.assertEqual(carte.get_descriere(), 'alta descriere')

    def test_cauta_dupa_titlu(self):
        lista = StorageInformation()
        carte = Carti(0, 'titlu', 'autor', 'ceva descriere', 23)
        lista.adaugare_in_lista(carte)

        rezultat_gasire = ServiceCarti.cauta_dupa_titlu(lista, 'titlu')
        self.assertEqual(rezultat_gasire, carte)

        rezultat_gasire = ServiceCarti.cauta_dupa_titlu(lista, 'titlul')
        self.assertEqual(rezultat_gasire, 0)

    def test_cauta_dupa_autor(self):
        lista = StorageInformation()
        carte = Carti(0, 'titlu', 'autor', 'ceva descriere', 23)
        lista.adaugare_in_lista(carte)

        rezultat_gasire = ServiceCarti.cauta_dupa_autor(lista, 'autor', 0)
        self.assertEqual(rezultat_gasire, carte)

        rezultat_gasire = ServiceCarti.cauta_dupa_autor(lista, 'autorrr', 0)
        self.assertEqual(rezultat_gasire, 0)

    def run_carti_tests(self):
        TestsCarti.test_modifica_titlu(self)
        TestsCarti.test_cauta_dupa_autor(self)
        TestsCarti.test_modifica_autor(self)
        TestsCarti.test_modifica_descriere(self)
        TestsCarti.test_cauta_dupa_titlu(self)


class ServiceClienti:
    @staticmethod
    def modifica_nume(lista, id_obj, new_nume):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_obj:
                el.set_nume(new_nume)
        return lista

    @staticmethod
    def modifica_prenume(lista, id_obj, new_prenume):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_obj:
                el.set_prenume(new_prenume)
        return lista

    @staticmethod
    def modifica_cnp(lista, id_obj, new_cnp):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_obj:
                el.set_cnp(new_cnp)
        return lista

    @staticmethod
    def cauta_dupa_nume(lista, nume):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_nume() == nume:
                return el
        return 0

    @staticmethod
    def cauta_dupa_prenume(lista, prenume):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_prenume() == prenume:
                return el
        return 0

    @staticmethod
    def adauga_carte_client(lista, id_client, titlu_carte):
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_id() == id_client:
                el.adauga_carte_inchiriata(titlu_carte)

                return lista

    @staticmethod
    def cauta_carte_inchiriata(client, titlu):
        lista_carti_inchiriate = client.get_carti_inchiriate()

        for i in lista_carti_inchiriate:
            if i == titlu:
                return False

        return True

    @staticmethod
    def sort_by_nume(client):
        return client.get_nume()

    @staticmethod
    def sort_by_nr_carti_inchiriate(client):
        return client.get_nr_inchirieri()

    @staticmethod
    def lista_cu_clienti_cu_carti(lista):
        lista_noua = StorageInformation()

        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)
            if el.get_nr_inchirieri() > 0:
                client_nou = Clienti(el.get_id(), el.get_nume(), el.get_prenume(), el.get_cnp(), el.get_nr_inchirieri())
                lista_carti_client = el.get_carti_inchiriate()
                client_nou.set_lista_carti(lista_carti_client)
                lista_noua.adaugare_in_lista_fara_id(client_nou)

        return lista_noua

    @staticmethod
    def clienti_cu_carti_inchiriate_sortat(lista):
        """functie care returneaza:
           -> o lista cu clientii care au inchiriat carti, sortata dupa nume (lista_noua_nume)
           -> o lista cu clientii care au inchiriat carti, sortata dupa nr de carti inchiriate (lista_noua_carti)
        """
        lista_noua_nume = StorageInformation()
        lista_noua_carti = StorageInformation()

        contor = 0

        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_nr_inchirieri() > 0:
                lista_noua_nume.adaugare_in_lista_fara_id(el)
                lista_noua_carti.adaugare_in_lista_fara_id(el)
                contor += 1

        # sortare lista dupa nume
        lista_noua_nume.sortare(ServiceClienti.sort_by_nume)

        # sortez lista dupa nr de carti
        lista_noua_carti.sortare(ServiceClienti.sort_by_nr_carti_inchiriate)

        return lista_noua_nume, lista_noua_carti

    @staticmethod
    def sort_by_nr_inchirieri(client):
        return client.get_nr_inchirieri()

    @staticmethod
    def cei_mai_activi_clienti(lista):
        """
        20% clienti activi
        :param lista: lista cu clienti
        :return:
        """
        lista_noua = StorageInformation()

        # copiez lista
        ServiceLista.copiaza_lista(lista, lista_noua)

        # sortez lista in functie de activitatea clientilor descrescator
        lista_noua.sortare_reversed(ServiceClienti.sort_by_nr_inchirieri)

        # partitionez lista (pentru a lua doar cei 20% din clienti)
        lista_noua.taiere_lista()

        return lista_noua

    @staticmethod
    def cei_mai_activi_clienti_bingo_sort(lista, functie):
        lista_noua = StorageInformation()

        # copiez lista
        ServiceLista.copiaza_lista(lista, lista_noua)

        ServiceClienti.Sort.bingo_sort(lista_noua, lista_noua.get_len_lista(), functie)

        lista_noua.taiere_lista()

        return lista_noua

    class Sort:
        @staticmethod
        def merge_sort_comparare(e1, e2, functie):
            return functie(e1) <= functie(e2)

        @staticmethod
        def merge(lista, stanga, mijloc, dreapta, functie):
            """
            sortare ordonat dupa nume
            :param lista: o lista de clienti
            :param stanga: pozitia minima din lista de la care se face sortarea
            :param mijloc: pozitia din mijloc din lista
            :param dreapta: pozitia maxima din lista pana la care se face sortarea
            :param functie: functie care determina criteriul dupa care se face compararea
            :return: o lista de clienti sortata dupa nume
            """
            n1 = mijloc - stanga + 1
            n2 = dreapta - mijloc

            # creez liste temporare si copiez informatiile
            left_array = lista.return_sliced_lista(stanga, mijloc)
            right_array = lista.return_sliced_lista(mijloc + 1, dreapta)

            # interclasez cele doua liste temporare in lista[stanga...dreapta]
            i = 0  # Indexul initial al primei liste
            j = 0  # Indexul initial al celei de a doua liste
            k = stanga  # Indexul initial al listei interclasate

            while i < n1 and j < n2:
                e1 = left_array.get_el_by_id(i)
                e2 = right_array.get_el_by_id(j)

                if ServiceClienti.Sort.merge_sort_comparare(e1, e2, functie):
                    lista.pune_pe_pozitia_k(e1, k)
                    i += 1
                else:
                    lista.pune_pe_pozitia_k(e2, k)
                    j += 1
                k += 1

            # copiez elementele ramase din prima lista temporara, daca mai sunt
            while i < n1:
                e1 = left_array.get_el_by_id(i)
                lista.pune_pe_pozitia_k(e1, k)
                i += 1
                k += 1

            # copiez elementele ramase din a doua lista temporara, daca mai sunt
            while j < n2:
                e2 = right_array.get_el_by_id(j)
                lista.pune_pe_pozitia_k(e2, k)
                j += 1
                k += 1

        @staticmethod
        def merge_sort(lista, stanga, dreapta, functie):
            if stanga < dreapta:
                mijloc = stanga + (dreapta - stanga) // 2

                ServiceClienti.Sort.merge_sort(lista, stanga, mijloc, functie)
                ServiceClienti.Sort.merge_sort(lista, mijloc + 1, dreapta, functie)
                ServiceClienti.Sort.merge(lista, stanga, mijloc, dreapta, functie)
            else:
                return

        @staticmethod
        def bingo_sort_comparare_egal(e1, e2, functie):
            return functie(e1) == functie(e2)

        @staticmethod
        def bingo_sort_comparare_greater(e1, e2, functie):
            return functie(e1) > functie(e2)

        @staticmethod
        def bingo_sort(lista, size, functie):
            """
            bingo sort, dar acest algoritm ordineaza o lista de clienti in ordine descrescatoare
            a numarului de carti inchiriate
            :param lista: o lista de clienti
            :param size: numarul de clienti din lista
            :param functie: criteriul duopa care se face sortarea
            :return: o lista de clienti sortata descrescator dupa numarul de inchirieri facute
            """
            # Caut clientul cu cele mai multe inchirieri
            bingo = lista.get_client_cu_cele_mai_multe_inchirieri()

            # Caut clientul cu cele mai putine inchirieri
            smallest = lista.get_client_cu_inchirieri_minime()
            next_bingo = smallest
            next_pos = 0
            while ServiceClienti.Sort.bingo_sort_comparare_greater(bingo, next_bingo, functie):
                # Tin in variabila next_pos locul unde trebuie sa interschimb
                # elementul care este egal cu bingo
                # incep verificarea de la start_pos, care e egal cu pozitia unde voi pune
                # urmatorul element bingo (next_pos)
                start_pos = next_pos
                for i in range(start_pos, size):
                    el = lista.get_de_pe_pozitia_k(i)
                    if ServiceClienti.Sort.bingo_sort_comparare_egal(el, bingo, functie):
                        # swap elementele de pe pozitiile i si next_pos
                        lista.swap_elemente(i, next_pos)
                        next_pos += 1

                    #  Aici gasim urmatorul element bingo (cel mai mare element mai mic decat maximul curent)
                    #  pentru urmatorul pas
                    elif ServiceClienti.Sort.bingo_sort_comparare_greater(el, next_bingo, functie):
                        next_bingo = el

                bingo = next_bingo
                next_bingo = smallest


class TestsClienti(unittest.TestCase):
    def test_modifica_nume(self):
        lista = StorageInformation()
        client = Clienti(0, 'nume', 'prenume', 2222222222222, 0)
        lista.adaugare_in_lista(client)

        lista = ServiceClienti.modifica_nume(lista, client.get_id(), 'alt_nume')

        client = lista.get_el_by_id(0)
        self.assertEqual(client.get_nume(), 'alt_nume')

    def test_modifica_prenume(self):
        lista = StorageInformation()
        client = Clienti(0, 'nume', 'prenume', 2222222222222, 0)
        lista.adaugare_in_lista(client)

        lista = ServiceClienti.modifica_prenume(lista, client.get_id(), 'alt_prenume')

        client = lista.get_el_by_id(0)
        self.assertEqual(client.get_prenume(), 'alt_prenume')

    def test_cauta_dupa_nume(self):
        lista = StorageInformation()
        client = Clienti(0, 'nume', 'prenume', 2222222222222, 0)
        lista.adaugare_in_lista(client)

        rezultat_gasit = ServiceClienti.cauta_dupa_nume(lista, client.get_nume())
        self.assertEqual(rezultat_gasit, client)

        rezultat_gasit = ServiceClienti.cauta_dupa_nume(lista, 'ALT_NUME')
        self.assertEqual(rezultat_gasit, 0)

    def test_adauga_carte_client(self):
        lista = StorageInformation()
        client = Clienti(0, 'nume', 'prenume', 2222222222222, 0)
        lista.adaugare_in_lista(client)

        lista = ServiceClienti.adauga_carte_client(lista, client.get_id(), 'Micul Print')

        lista_carti = client.get_carti_inchiriate()
        self.assertEqual(lista_carti[0], 'Micul Print')

        ServiceClienti.adauga_carte_client(lista, client.get_id(), 'Azzz')

        lista_carti = client.get_carti_inchiriate()
        self.assertEqual(lista_carti[1], 'Azzz')

    def test_merge_sort(self):
        client1 = Clienti(0, 'nume', 'prenume', 1234567898765, 0)
        client2 = Clienti(1, 'z_nume', 'z_prenume', 9876543212345, 0)
        client3 = Clienti(2, 'alt_nume', 'alt_prenume', 6545676545654, 0)

        lista = StorageInformation()
        lista.adaugare_in_lista(client1)
        lista.adaugare_in_lista(client2)
        lista.adaugare_in_lista(client3)

        ServiceClienti.Sort.merge_sort(lista, 0, 2, Clienti.get_nume)

        self.assertEqual(lista.get_el_by_id(0), client3)
        self.assertEqual(lista.get_el_by_id(1), client1)
        self.assertEqual(lista.get_el_by_id(2), client2)

    def test_bingo_sort(self):
        client1 = Clienti(0, 'nume', 'prenume', 1234567898765, 7)
        client2 = Clienti(1, 'z_nume', 'z_prenume', 9876543212345, 4)
        client3 = Clienti(2, 'alt_nume', 'alt_prenume', 6545676545654, 5)
        client4 = Clienti(3, 'alt_nume_2', 'alt_prenume_2', 2345263245324, 7)

        lista = StorageInformation()

        lista.adaugare_in_lista(client1)
        lista.adaugare_in_lista(client2)
        lista.adaugare_in_lista(client3)
        lista.adaugare_in_lista(client4)

        ServiceClienti.Sort.bingo_sort(lista, lista.get_len_lista(), Clienti.get_nr_inchirieri)

        self.assertEqual(lista.get_el_by_id(0), client1)
        self.assertEqual(lista.get_el_by_id(1), client4)
        self.assertEqual(lista.get_el_by_id(2), client3)
        self.assertEqual(lista.get_el_by_id(3), client2)

    def test_cei_mai_activi_clienti_cu_bingo_sort(self):
        lista = StorageInformation()

        client1 = Clienti(0, 'nume', 'prenume', 1234567898765, 4)
        client2 = Clienti(1, 'z_nume', 'z_prenume', 9876543212345, 7)
        client3 = Clienti(2, 'alt_nume', 'alt_prenume', 6545676545654, 5)
        client4 = Clienti(3, 'alt_nume_2', 'alt_prenume_2', 2345263245324, 0)

        lista.adaugare_in_lista(client1)
        lista.adaugare_in_lista(client2)
        lista.adaugare_in_lista(client3)
        lista.adaugare_in_lista(client4)

        lista_noua = ServiceClienti.cei_mai_activi_clienti_bingo_sort(lista, Clienti.get_nr_inchirieri)

        self.assertEqual(lista_noua.get_len_lista(), 1)
        self.assertEqual(lista_noua.get_el_by_id(0), client2)

    def run_clienti_tests(self):
        TestsClienti.test_modifica_nume(self)
        TestsClienti.test_modifica_prenume(self)
        TestsClienti.test_cauta_dupa_nume(self)
        TestsClienti.test_adauga_carte_client(self)
        TestsClienti.test_merge_sort(self)
        TestsClienti.test_bingo_sort(self)
        TestsClienti.test_cei_mai_activi_clienti_cu_bingo_sort(self)


class ServiceTests:
    @staticmethod
    def run_all_tests():
        teste_clienti = TestsClienti()
        teste_clienti.run_clienti_tests()

        teste_carti = TestsCarti()
        teste_carti.run_carti_tests()
