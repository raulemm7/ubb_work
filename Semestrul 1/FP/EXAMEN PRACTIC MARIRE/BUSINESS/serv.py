import random
from DOMAIN.entities import Baller
from REPOSITORY.repo import Repo
from VALIDATOR.validare import Vali


class Service:
    @staticmethod
    def append_jucator(lista_jucatori, nume, prenume, post, inaltime):
        """
        creeaza un nou jucator si il adauga la finalul listei
        :param lista_jucatori: lista in care se va adauga noul jucator
        :param nume: numele jucatorului citit de la tastatura
        :param prenume: prenumele jucatorului citit de la tastatura
        :param post: un string din lista ['Extrema', 'Pivot', 'Fundas']
        :param inaltime: un intreg > 140
        :return: None
        """
        ent = Baller(nume, prenume, post, inaltime)
        lista_jucatori.append_ent(ent)

    @staticmethod
    def find_minim_h(lista):
        """
        returneaza cea mai mica inaltime dintr o lista de jucatori
        :param lista: lista in care se face cautarea
        :return: numar intreg
        """
        minim = 23123
        for i in range(0, lista.get_len()):
            ent = lista.get_ent(i)

            if ent.get_inaltime() < minim:
                minim = ent.get_inaltime()

        return minim

    @staticmethod
    def modifica_inaltime_jucatori(lista, delta_h):
        """
        modifica inaltimea tuturor jucatorilor din lista cu delta_h
        :param lista: lista de jucatori in care se face modificarea
        :param delta_h: numarul cu cat se modifica inaltimea fiecarui jucator
        :return: None
        """
        for i in range(0, lista.get_len()):
            ent = lista.get_ent(i)

            h_curent = ent.get_inaltime()
            h_curent += delta_h
            ent.set_inaltime(h_curent)

    @staticmethod
    def creeaza_echipa(lista_jucatori):
        """
        functia primeste o lista cu jucatori si returneaza o alta lista formata doar din 5 jucatori
        a carei inaltime medie este cea mai mare
        :param lista_jucatori: lista din care se iau jucatorii pentru a forma o echipa
        :return: o lista cu 5 entitati
        """
        if lista_jucatori.get_len() < 5:
            return [], 'Nu exista suficienti jucatori pentru a crea o echipa!'

        # sortez mai intai echipa dupa inaltime
        lista = lista_jucatori.get_all()
        lista.sort(key=Baller.get_inaltime, reverse=True)

        lista_cu_echipa = []

        pivoti = 0
        extreme = 0
        fundasi = 0

        for ent in lista:
            post = ent.get_post()

            if post == 'Pivot' and pivoti < 1:
                lista_cu_echipa.append(ent)
                pivoti += 1
            elif post == 'Extrema' and extreme < 2:
                lista_cu_echipa.append(ent)
                extreme += 1
            elif post == 'Fundas' and fundasi < 2:
                lista_cu_echipa.append(ent)
                fundasi += 1

        if pivoti != 1 or extreme != 2 or fundasi != 2:
            return [], 'Nu exista suficienti jucatori care sa satisfaca criteriile!'

        return lista_cu_echipa, 'ok'

    @staticmethod
    def importa_jucatori_din_fisier(lista_jucatori, new_file):
        """
        citeste numele si prenumele unor jucatori dintr un fisier si ii adauga in lista de jucatori daca nu
        exista deja, postul si inaltimea lor fiind generate random
        :param lista_jucatori: lista de jucatori in care se vor salva noii jucatori
        :param new_file: fisierul din care se face citirea
        :return: nr de jucatori importati, nr total de persoane citite din fisier
        """
        lista_posturi = ['Pivot', 'Extrema', 'Fundas']
        nr_jucatori_importati = 0
        nr_total_jucatori = 0

        inp = new_file.open_file_for_read()
        for line in inp:
            nr_total_jucatori += 1

            line = line.strip()
            parts = line.split('/')

            nume = parts[0]
            prenume = parts[1]

            rez, mes = Vali.valideaza_nume_prenume(lista_jucatori, nume, prenume)
            if rez:
                # inseamna ca nu exista jucator cu acest nume si prenume, il adaugam
                poz = random.randint(0, 2)
                post = lista_posturi[poz]

                h = random.randint(141, 220)

                ent = Baller(nume, prenume, post, h)
                lista_jucatori.append_ent(ent)
                nr_jucatori_importati += 1

        new_file.close_file(inp)
        return nr_jucatori_importati, nr_total_jucatori


class ServiceTests:
    @staticmethod
    def run_all_tests():
        ServiceTests.test_find_minim_h()
        ServiceTests.test_modifica_h()
        ServiceTests.test_creeaza_echipa()

    @staticmethod
    def test_find_minim_h():
        lista = Repo()
        ent1 = Baller('Dragusin', 'Ionut', 'Pivot', 178)
        lista.append_ent(ent1)
        ent2 = Baller('Dumitrescu', 'Florin', 'Extrema', 182)
        lista.append_ent(ent2)

        assert Service.find_minim_h(lista) == 178

    @staticmethod
    def test_modifica_h():
        lista = Repo()
        ent1 = Baller('Dragusin', 'Ionut', 'Pivot', 178)
        lista.append_ent(ent1)
        ent2 = Baller('Dumitrescu', 'Florin', 'Extrema', 182)
        lista.append_ent(ent2)

        Service.modifica_inaltime_jucatori(lista, -12)

        ent1 = lista.get_ent(0)
        assert ent1.get_inaltime() == 166

        ent2 = lista.get_ent(1)
        assert ent2.get_inaltime() == 170

    @staticmethod
    def test_creeaza_echipa():
        lista = Repo()
        ent1 = Baller('Dragusin', 'Ionut', 'Pivot', 178)
        lista.append_ent(ent1)
        ent2 = Baller('Dumitrescu', 'Florin', 'Extrema', 182)
        lista.append_ent(ent2)

        rezultat, mesaj = Service.creeaza_echipa(lista)
        assert rezultat == []
        assert mesaj == 'Nu exista suficienti jucatori pentru a crea o echipa!'

        ent3 = Baller('Test1', 'Test2', 'Extrema', 198)
        ent4 = Baller('Test2', 'Test4', 'Fundas', 205)
        ent5 = Baller('Test5', 'Test3', 'Extrema', 189)
        lista.append_ent(ent3)
        lista.append_ent(ent4)
        lista.append_ent(ent5)

        rezultat, mesaj = Service.creeaza_echipa(lista)
        assert rezultat == []
        assert mesaj == 'Nu exista suficienti jucatori care sa satisfaca criteriile!'

        ent6 = Baller('Test54', 'Test443', 'Fundas', 201)
        lista.append_ent(ent6)

        rezultat, mesaj = Service.creeaza_echipa(lista)
        assert mesaj == 'ok'
        assert rezultat == [ent4, ent6, ent3, ent5, ent1]
