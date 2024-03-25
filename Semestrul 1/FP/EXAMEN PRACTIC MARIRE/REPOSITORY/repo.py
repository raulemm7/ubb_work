from DOMAIN.entities import Baller


class FileRepo:
    def __init__(self, file):
        self.__file = file

    def open_file_for_read(self):
        """
        deschide un fisier pentru citire
        :return: descriptorul de fisier
        """
        desc = open(self.__file, 'r+')
        return desc

    def open_file_for_write(self):
        """
        deschide un fisier pentru scriere
        :return: descriptorul fisierului
        """
        desc = open(self.__file, 'w+')
        return desc

    @staticmethod
    def close_file(desc):
        """
        inchide un fisier
        :param desc: descriptorul fisierului
        :return: None
        """
        desc.close()


class Repo:
    def __init__(self):
        self.__lista = []

    def get_len(self):
        """
        :return: lungimea unei liste de jucatori
        """
        return len(self.__lista)

    def get_ent(self, nr):
        """
        :param nr: pozitia entitatii care va fi returnata din lista
        :return: o entitate de tip Baller
        """
        return self.__lista[nr]

    def get_all(self):
        """
        :return: o lista cu toti jucatorii
        """
        return self.__lista

    def append_ent(self, ent):
        """
        adauga la finalul listei o noua entitate
        :param ent: entitatea care se va adauga
        :return: None
        """
        self.__lista.append(ent)

    def clear_list(self):
        """
        sterge informatiile din lista
        :return: None
        """
        self.__lista.clear()

    def read_from_file(self, file):
        """
        citeste informatiile dintr un fisier si le adauga intr o lista de jucatori
        :param file: fisierul din care se face citirea
        :return: None
        """
        inp = file.open_file_for_read()

        for line in inp:
            line = line.strip()
            parts = line.split('/')

            nume = parts[0]
            prenume = parts[1]
            post = parts[2]
            inaltime = int(parts[3])

            ent = Baller(nume, prenume, post, inaltime)

            self.append_ent(ent)

        file.close_file(inp)

    def write_in_file(self, file):
        """
        scrie intr un fisier informatiile jucatorilor dintr o lista
        :param file: fisierul in care se face scrierea
        :return: None
        """
        out = file.open_file_for_write()

        for i in range(0, self.get_len()):
            ent = self.get_ent(i)

            info = ''
            info += ent.get_nume()
            info += '/'
            info += ent.get_prenume()
            info += '/'
            info += ent.get_post()
            info += '/'
            info += str(ent.get_inaltime())
            info += '\n'

            out.write(info)

        file.close_file(out)


class RepoTests:
    @staticmethod
    def run_all_tests():
        RepoTests.test_citire_scriere_fisier()
        RepoTests.test_list()

    @staticmethod
    def test_citire_scriere_fisier():
        file = FileRepo('test_file.txt')
        informatie = 'verificare executie metode lucru fisier/'

        out = file.open_file_for_write()
        out.write(informatie)

        file.close_file(out)

        # verific daca s a scris corect
        inp = file.open_file_for_read()
        for line in inp:
            line = line.strip()
            parts = line.split('/')

            assert parts[0] == 'verificare executie metode lucru fisier'

        file.close_file(inp)

        # resetez fisierul de test
        out = file.open_file_for_write()
        out.write("")
        file.close_file(out)

    @staticmethod
    def test_list():
        lista = Repo()
        ent = Baller('Tanase', 'Mirel', 'Pivot', 176)

        lista.append_ent(ent)
        assert lista.get_ent(0) == ent
        assert lista.get_len() == 1

        lista.clear_list()
        assert lista.get_len() == 0
