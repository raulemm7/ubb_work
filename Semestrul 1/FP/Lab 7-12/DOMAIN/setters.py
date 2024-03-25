import unittest


class Carti:
    def __init__(self, id_carte, titlu, autor, descriere, contor_inchirieri):
        self.__id_carte = id_carte
        self.__titlu = titlu
        self.__autor = autor
        self.__descriere = descriere
        self.__contor_inchirieri = contor_inchirieri        # repr nr de exemplare ramase disponibile spre inchiriere
        self.__nr_total_de_exemplare = contor_inchirieri    # nr total de exemplare valabile

    def get_id(self):
        return self.__id_carte

    def get_titlu(self):
        return self.__titlu

    def get_autor(self):
        return self.__autor

    def get_descriere(self):
        return self.__descriere

    def get_nr_inchirieri(self):
        return self.__contor_inchirieri

    def get_nr_total_de_exemplare(self):
        return self.__nr_total_de_exemplare

    def get_nr_exemplare_inchiriate(self):
        return self.__nr_total_de_exemplare - self.__contor_inchirieri

    def set_id(self, new_id):
        self.__id_carte = new_id

    def set_titlu(self, new_titlu):
        self.__titlu = new_titlu

    def set_autor(self, new_autor):
        self.__autor = new_autor

    def set_descriere(self, new_descriere):
        self.__descriere = new_descriere

    def set_nr_inchirieri(self, new_contor):
        self.__contor_inchirieri = new_contor


class TestsCarti(unittest.TestCase):
    def test_getters(self):
        carte = Carti(0, 'titlu', 'autor', 'descriere succinta', 12)

        self.assertEqual(carte.get_id(), 0)
        self.assertEqual(carte.get_titlu(), 'titlu')
        self.assertEqual(carte.get_autor(), 'autor')
        self.assertEqual(carte.get_descriere(), 'descriere succinta')
        self.assertEqual(carte.get_nr_inchirieri(), 12)

    def test_setters(self):
        carte = Carti(0, 'titlu', 'autor', 'descriere succinta', 12)

        carte.set_id(1)
        carte.set_titlu('alt_titlu')
        carte.set_autor('alt_autor')
        carte.set_descriere('alta descriere succinta')
        carte.set_nr_inchirieri(21)

        self.assertEqual(carte.get_id(), 1)
        self.assertEqual(carte.get_autor(), 'alt_autor')
        self.assertEqual(carte.get_titlu(), 'alt_titlu')
        self.assertEqual(carte.get_descriere(), 'alta descriere succinta')
        self.assertEqual(carte.get_nr_inchirieri(), 21)

    def run_carte_tests(self):
        TestsCarti.test_getters(self)
        TestsCarti.test_setters(self)


class Clienti:
    def __init__(self, id_client, nume, prenume, cnp, contor):
        self.__id_client = id_client
        self.__nume = nume
        self.__prenume = prenume
        self.__cnp = cnp
        self.__contor = contor          # repr nr de carti inchiriate
        self.__lista_carti = []

    def get_id(self):
        return self.__id_client

    def get_nume(self):
        return self.__nume

    def get_prenume(self):
        return self.__prenume

    def get_cnp(self):
        return self.__cnp

    def get_nr_inchirieri(self):
        return self.__contor

    def get_carti_inchiriate(self):
        return self.__lista_carti

    def set_nr_inchirieri(self, new_nr):
        self.__contor = new_nr

    def set_id(self, new_id):
        self.__id_client = new_id

    def set_nume(self, new_nume):
        self.__nume = new_nume

    def set_prenume(self, new_prenume):
        self.__prenume = new_prenume

    def set_cnp(self, new_cnp):
        self.__cnp = new_cnp

    def set_lista_carti(self, new_lista_carti):
        self.__lista_carti = new_lista_carti

    def adauga_carte_inchiriata(self, titlu_carte):
        self.__lista_carti.append(0)
        self.__lista_carti[self.__contor] = titlu_carte
        self.__contor += 1

    def sterge_carte_returnata(self, titlu_carte):
        for i in self.__lista_carti:
            if i == titlu_carte:
                self.__lista_carti.remove(i)
                self.__contor -= 1

                break


class TestsClienti(unittest.TestCase):
    def test_getters(self):
        client = Clienti(0, 'nume', 'prenume', 1234567898765, 12)

        self.assertEqual(client.get_id(), 0)
        self.assertEqual(client.get_nume(), 'nume')
        self.assertEqual(client.get_prenume(), 'prenume')
        self.assertEqual(client.get_cnp(), 1234567898765)
        self.assertEqual(client.get_nr_inchirieri(), 12)

    def test_setters(self):
        client = Clienti(0, 'nume', 'prenume', 1234567898765, 12)

        client.set_id(3)
        client.set_nume('ALT_NUME')
        client.set_prenume('ALT_PRENUME')
        client.set_cnp(9876543212345)
        client.set_nr_inchirieri(321)

        self.assertEqual(client.get_id(), 3)
        self.assertEqual(client.get_nume(), 'ALT_NUME')
        self.assertEqual(client.get_prenume(), 'ALT_PRENUME')
        self.assertEqual(client.get_cnp(), 9876543212345)
        self.assertEqual(client.get_nr_inchirieri(), 321)

    def run_client_tests(self):
        TestsClienti.test_getters(self)
        TestsClienti.test_setters(self)


class DomainTests:
    @staticmethod
    def run_tests():
        test_carti = TestsCarti()
        test_carti.run_carte_tests()

        test_client = TestsClienti()
        test_client.run_client_tests()
