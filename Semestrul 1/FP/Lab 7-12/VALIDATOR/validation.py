from REPOSITORY.storage import StorageInformation
from DOMAIN.setters import Clienti, Carti


class Validator:
    @staticmethod
    def validare_nume(lista, nume, prenume):
        """functie care verifica daca la introducerea unui nou client acesta nu exista deja"""
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)
            if el.get_nume() == nume and el.get_prenume() == prenume:
                return False

        return True

    @staticmethod
    def test_validare_nume():
        lista = StorageInformation()
        client = Clienti(0, 'andrei', 'vlad', 1111111111111, 0)
        lista.adaugare_in_lista(client)

        assert not Validator.validare_nume(lista, 'andrei', 'vlad')
        assert Validator.validare_nume(lista, 'popescu', 'mircea')

    @staticmethod
    def validare_titlu_carte(lista, titlu):
        """functie care verifica daca la introducerea unei noi carti, aceasta nu exista deja"""
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)
            if el.get_titlu() == titlu:
                return False

        return True

    @staticmethod
    def test_validare_titlu_carte():
        lista = StorageInformation()
        carte = Carti(0, 'titlu', 'autor', 'o descriere ceva', 12)
        lista.adaugare_in_lista(carte)

        assert not Validator.validare_titlu_carte(lista, 'titlu')
        assert Validator.validare_titlu_carte(lista, 'Alt titlu')

    class Tests:
        @staticmethod
        def run_validator_tests():
            Validator.test_validare_nume()
            Validator.test_validare_titlu_carte()
