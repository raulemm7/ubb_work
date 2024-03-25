from DOMAIN.entities import Baller
from REPOSITORY.repo import Repo


class Vali:
    @staticmethod
    def valideaza_nume_prenume(lista, nume, prenume):
        """
        verifica daca exista deja in lista de informatii un jucator cu numele si prenumele primite prin parametrii
        sau daca aceste variabile sunt string uri vide
        :param lista: lista de jucatori in care se face verificarea
        :param nume: numele pentru care se face verificarea
        :param prenume: prenumele pentru care se face verificarea
        :return: True/False: daca nu s a gasit un jucator cu aceste informatii/daca exista deja un jucator
                 Mesaj: un mesaj pentru a atentiona utilizatorul eroarea depistata
        """
        for i in range(0, lista.get_len()):
            ent = lista.get_ent(i)

            if ent.get_nume() == nume and ent.get_prenume() == prenume:
                return False, 'Jucatorul pe care doresti sa il introduci exista deja, introdu alt jucator!'

        nume = nume.strip()
        prenume = prenume.strip()

        if nume == '' or prenume == '':
            return False, 'Numele si prenumele nu pot fi vide, introdu alte informatii!'

        return True, 'ok'


class ValiTests:
    @staticmethod
    def run_all_tests():
        ValiTests.test_valideaza_nume_prenume()

    @staticmethod
    def test_valideaza_nume_prenume():
        lista = Repo()
        ent1 = Baller('Dragusin', 'Ionut', 'Pivot', 178)
        lista.append_ent(ent1)
        ent2 = Baller('Dumitrescu', 'Florin', 'Extrema', 182)
        lista.append_ent(ent2)

        rez, mesaj = Vali.valideaza_nume_prenume(lista, 'Dragusin', 'Ionut')
        assert not rez
        assert mesaj == 'Jucatorul pe care doresti sa il introduci exista deja, introdu alt jucator!'

        rez, mesaj = Vali.valideaza_nume_prenume(lista, ' ', 'Mircea')
        assert not rez
        assert mesaj == 'Numele si prenumele nu pot fi vide, introdu alte informatii!'

        rez, mesaj = Vali.valideaza_nume_prenume(lista, 'Nikolic', 'Ionut')
        assert rez
        assert mesaj == 'ok'
