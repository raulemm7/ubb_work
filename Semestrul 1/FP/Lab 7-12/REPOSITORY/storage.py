import unittest
from DOMAIN.setters import Carti, Clienti


class StorageInformation:
    def __init__(self):
        self.__lista = []
        self.__exemplare_valabile = 0

    def adaugare_in_lista(self, element):
        """adauga un element in lista pe pozitia [id_element]"""
        self.__lista.append(0)
        self.__lista[element.get_id()] = element

    def adaugare_in_lista_fara_id(self, element):
        self.__lista.append(element)

    def pune_pe_pozitia_k(self, element, pozitie):
        self.__lista[pozitie] = 0
        self.__lista[pozitie] = element

    def get_de_pe_pozitia_k(self, pozitie):
        return self.__lista[pozitie]

    def swap_elemente(self, i, j):
        self.__lista[i], self.__lista[j] = self.__lista[j], self.__lista[i]

    def return_sliced_lista(self, poz_inceput, poz_sfarsit):
        lista = StorageInformation()

        lista_cu_elemente = self.__lista
        lista_cu_elemente = lista_cu_elemente[poz_inceput:poz_sfarsit + 1]

        for el in lista_cu_elemente:
            lista.adaugare_in_lista_fara_id(el)
        return lista

    def stergere_lista(self):
        """sterge toate elementele din lista"""
        self.__lista.clear()

    def stergere_din_lista(self, id_element):
        """sterge elementul de pe pozitia [id_element]"""
        self.__lista.pop(id_element)

    def get_len_lista(self):
        """returneaza lungimea listei"""
        return len(self.__lista)

    def get_lista_cu_elemente(self):
        return self.__lista

    def get_el_by_id(self, id_el):
        """returneaza elementul de pe pozitia [id_element]"""
        return self.__lista[id_el]

    def set_exemplare_valabile(self, nr_exemplare):
        self.__exemplare_valabile += nr_exemplare

    def get_exemplare_valabile(self):
        return self.__exemplare_valabile

    def sortare(self, functie):
        """sorteaza lista crescator in functie de criteriul functie"""
        self.__lista.sort(key=functie)

    def sortare_reversed(self, functie):
        """sorteaza lista descrescator in functie de criteriul functie"""
        self.__lista.sort(key=functie, reverse=True)

    def taiere_lista(self):
        """se taie lista astfel incat sa ramana primele 20% elemente din ea"""
        contor = self.get_len_lista() // 5

        # in caz ca 20% din nr de el = 0, acest nr va fi 1 pentru a afisa macar un element
        if contor == 0:
            contor = 1

        self.__lista = self.__lista[:contor]

    def get_client_cu_cele_mai_multe_inchirieri(self):
        el_cautat = self.__lista[0]
        nr_max = el_cautat.get_nr_inchirieri()

        for i in range(1, len(self.__lista)):
            el = self.__lista[i]
            if el.get_nr_inchirieri() > nr_max:
                el_cautat = el
                nr_max = el.get_nr_inchirieri()

        return el_cautat

    def get_client_cu_inchirieri_minime(self):
        el_cautat = self.__lista[0]
        nr_min = el_cautat.get_nr_inchirieri()

        for i in range(1, len(self.__lista)):
            el = self.__lista[i]
            if el.get_nr_inchirieri() < nr_min:
                el_cautat = el
                nr_min = el.get_nr_inchirieri()

        return el_cautat

    def load_from_file_carti(self, file):
        input_file = file.open_for_read()

        id_carte = self.get_len_lista()
        nr_exemplare = 0

        for line in input_file:
            line = line.strip()
            parts = line.split(';')

            # datele din fisier
            # titlu;autor;descriere;nr_total_exemplare
            carte = Carti(id_carte, parts[0], parts[1], parts[2], int(parts[3]))

            self.adaugare_in_lista(carte)
            id_carte += 1
            nr_exemplare += int(parts[3])

        self.set_exemplare_valabile(nr_exemplare)

        file.close_file(input_file)

    def load_from_file_clienti(self, file):
        input_file = file.open_for_read()

        id_client = self.get_len_lista()

        for line in input_file:
            line = line.strip()
            parts = line.split(';')

            # informatiile din fisier
            # nume;prenume;cnp
            client = Clienti(id_client, parts[0], parts[1], int(parts[2]), 0)
            self.adaugare_in_lista(client)

            id_client += 1

        file.close_file(input_file)

    def write_in_file_carti(self, file):
        output_file = file.open_for_append()

        for i in range(0, self.get_len_lista()):
            element = self.get_el_by_id(i)

            informatie = ""
            informatie += str(element.get_titlu())
            informatie += ';'
            informatie += str(element.get_autor())
            informatie += ';'
            informatie += str(element.get_descriere())
            informatie += ';'
            informatie += str(element.get_nr_total_de_exemplare())
            informatie += '\n'

            output_file.write(informatie)

        file.close_file(output_file)

    def write_in_file_clienti(self, file):
        output_file = file.open_for_append()

        for i in range(0, self.get_len_lista()):
            element = self.get_el_by_id(i)

            informatie = ""
            informatie += str(element.get_nume())
            informatie += ';'
            informatie += str(element.get_prenume())
            informatie += ';'
            informatie += str(element.get_cnp())
            informatie += '\n'

            output_file.write(informatie)

        file.close_file(output_file)


class StorageInformationTests(unittest.TestCase):
    def test_adaugare_in_lista(self):
        lista = StorageInformation()

        carte = Carti(0, 'titlu', 'autor', 'descriere', 12)
        lista.adaugare_in_lista(carte)
        self.assertEqual(lista.get_el_by_id(carte.get_id()), carte)

        carte = Carti(1, 'titlu2', 'autor2', 'descriere2', 12)
        lista.adaugare_in_lista(carte)
        self.assertEqual(lista.get_el_by_id(carte.get_id()), carte)

    def test_stergere_lista(self):
        lista = StorageInformation()

        carte = Carti(0, 'titlu', 'autor', 'descriere', 12)
        lista.adaugare_in_lista(carte)

        carte = Carti(1, 'titlu2', 'autor2', 'descriere2', 12)
        lista.adaugare_in_lista(carte)

        lista.stergere_lista()
        self.assertEqual(lista.get_len_lista(), 0)

    def test_stergere_din_lista(self):
        lista = StorageInformation()

        carte1 = Carti(0, 'titlu', 'autor', 'descriere', 12)
        lista.adaugare_in_lista(carte1)

        carte2 = Carti(1, 'titlu2', 'autor2', 'descriere2', 12)
        lista.adaugare_in_lista(carte2)

        lista.stergere_din_lista(0)
        self.assertEqual(lista.get_el_by_id(0), carte2)

    def test_get_len_lista(self):
        lista = StorageInformation()

        carte = Carti(0, 'titlu', 'autor', 'descriere', 12)
        lista.adaugare_in_lista(carte)

        carte = Carti(1, 'titlu2', 'autor2', 'descriere2', 12)
        lista.adaugare_in_lista(carte)

        self.assertEqual(lista.get_len_lista(), 2)

    def test_get_el_by_id(self):
        lista = StorageInformation()

        carte0 = Carti(0, 'titlu', 'autor', 'descriere', 12)
        lista.adaugare_in_lista(carte0)

        carte1 = Carti(1, 'titlu2', 'autor2', 'descriere2', 12)
        lista.adaugare_in_lista(carte1)

        self.assertEqual(lista.get_el_by_id(1), carte1)

    def run_storage_tests(self):
        StorageInformationTests.test_adaugare_in_lista(self)
        StorageInformationTests.test_stergere_lista(self)
        StorageInformationTests.test_stergere_din_lista(self)
        StorageInformationTests.test_get_len_lista(self)
        StorageInformationTests.test_get_el_by_id(self)


class FileStorage:
    def __init__(self, file):
        self.__file_path = file

    def open_for_read(self):
        input_file = open(self.__file_path, "r+")
        return input_file

    def open_for_append(self):
        input_file = open(self.__file_path, "a")
        return input_file

    @staticmethod
    def close_file(file):
        file.close()

    @staticmethod
    def delete_all_data_from_file(file):
        file.seek(0)
        file.truncate()


class FileStorageTests(unittest.TestCase):
    def test_open_for_append(self):
        file = FileStorage('carti_test.txt')
        input_file = file.open_for_append()

        input_file.write('titlu_2;autor_2;alta descriere;14')
        file.close_file(input_file)

        input_file = file.open_for_read()
        contor = 0
        for line in input_file:
            contor += 1
            if contor >= 2:
                line = line.strip()
                parts = line.split(';')

                self.assertEqual(parts[0], 'titlu_2')
                self.assertEqual(parts[1], 'autor_2')
                self.assertEqual(parts[2], 'alta descriere')
                self.assertEqual(int(parts[3]), 14)
        file.close_file(input_file)

    def test_delete_all_data_from_file(self):
        file = FileStorage('carti_test.txt')
        input_file = file.open_for_append()
        file.delete_all_data_from_file(input_file)
        file.close_file(input_file)

        input_file = file.open_for_read()
        line = input_file.readline()
        self.assertEqual(line, "")
        file.close_file(input_file)

    def run_file_tests(self):
        FileStorageTests.test_open_for_append(self)
        FileStorageTests.test_delete_all_data_from_file(self)
