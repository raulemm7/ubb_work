class Baller:
    def __init__(self, nume, prenume, post, inaltime):
        self.__nume = nume
        self.__prenume = prenume
        self.__post = post
        self.__inaltime = inaltime

    def set_nume(self, nume):
        self.__nume = nume

    def set_prenume(self, prenume):
        self.__prenume = prenume

    def set_post(self, post):
        self.__post = post

    def set_inaltime(self, inalt):
        self.__inaltime = inalt

    def get_nume(self):
        return self.__nume

    def get_prenume(self):
        return self.__prenume

    def get_post(self):
        return self.__post

    def get_inaltime(self):
        return self.__inaltime


class BallerTests:
    @staticmethod
    def run_all_tests():
        BallerTests.getters_tests()
        BallerTests.setters_tests()

    @staticmethod
    def getters_tests():
        ent = Baller('Steph', 'Curry', 'Pivot', 164)

        assert ent.get_nume() == 'Steph'
        assert ent.get_prenume() == 'Curry'
        assert ent.get_post() == 'Pivot'
        assert ent.get_inaltime() == 164

    @staticmethod
    def setters_tests():
        ent = Baller('Steph', 'Curry', 'Pivot', 164)
        ent.set_nume('Koby')
        ent.set_prenume('Bryant')
        ent.set_post('Extrema')
        ent.set_inaltime(189)

        assert ent.get_nume() == 'Koby'
        assert ent.get_prenume() == 'Bryant'
        assert ent.get_post() == 'Extrema'
        assert ent.get_inaltime() == 189
