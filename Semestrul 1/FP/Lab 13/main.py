class Functii:
    @staticmethod
    def verificare_solutie(lista) -> bool:
        """
        verifica daca o lista de elemente poate reprezenta o solutie
        :param lista: lista
        :return: True (daca solutia e corecta) || False(daca solutie este gresita)
        """
        nr_perechi = 0

        for el in lista:
            if el == '(':
                nr_perechi += 1
            else:
                nr_perechi -= 1

            if nr_perechi < 0:
                return False

        return nr_perechi == 0

    @staticmethod
    def print_lista(lista) -> None:
        """
        afiseaza formatat o solutie valida
        :param lista: o solutie
        :return: None
        """
        for i in lista:
            print(i, end='')
        print('')

    @staticmethod
    def print_all_lists(liste) -> None:
        """
        afiseaza toate solutiile gasite
        :param liste: lista de liste
        :return: None
        """
        for lista in liste:
            Functii.print_lista(lista)

    @staticmethod
    def copiere_lista(old) -> list:
        """
        copiaza o lista transmisa prin parametru, iar lista nou creata o returnez
        :param old: list
        :return: list
        """
        new = [0] * len(old)
        for i in range(0, len(old)):
            new[i] = old[i]

        return new

    @staticmethod
    def backtracking_recursiv(lista, pozitie, nr_total, lista_solutii) -> None:
        """
        bactracking recursiv
        A = {'(', ')'}
        S = A * A * ... * A (de nr_total ori, nr_total par)
        conditia de consistena: o solutie este corecta daca parantezele "se inchid" corect
        matematic: o solutie reprezinta o lista ale carei elemente apartin multimii {1, -1}
        1 = '('
        -1 = ')'
        o solutie este corecta daca:
        1) elementele din lista de sume partiale >= 0
        2) ultimul element din lista de sume partiale = 0
        3) primul element din lista de solutie este 1 ( '(' )
        4) ultimul element din lista de solutie este -1 ( ')' )

        :param lista: lista in care se face backtracking-ul
        :param pozitie: pozitia de la care se incepe
        :param nr_total: nr total de elemente pe care trebuie sa il aiba o solutie
        :param lista_solutii: lista in care retin solutiile (alte liste)
        :return: None
        """
        for i in ['(', ')']:
            lista[pozitie] = i

            if pozitie == nr_total - 1:
                if Functii.verificare_solutie(lista):
                    new = Functii.copiere_lista(lista)
                    lista_solutii.append(new)
            else:
                Functii.backtracking_recursiv(lista, pozitie + 1, nr_total, lista_solutii)

    @staticmethod
    def bkt_decoding(lista) -> list:
        """
        functia primeste o lista ale carei elemente apartin {1, 2}
        si returneaza o lista cu elemente ce apartin {'(', ')'}
        1 = '('
        2 = ')'
        :param lista: lista cu elemente numerice pentru care se face decodarea
        :return: o lista cu paranteze
        """
        new_list = ['('] * len(lista)
        for i in range(0, len(lista)):
            if lista[i] == 1:
                new_list[i] = '('
            else:
                new_list[i] = ')'
        return new_list

    @staticmethod
    def backtracking_iterativ(nr_total, lista_solutii) -> None:
        """
        backtracking iterativ
        A = {1, 2}
        S = A * A * ... * A (de nr_total ori, nr_total par)
        1 -> '('
        2 -> ')'
        conditia de consistena: o solutie este corecta daca parantezele "se inchid" corect
        matematic: o solutie reprezinta o lista ale carei elemente apartin multimii {1, -1}
        1 = '('
        -1 = ')'
        o solutie este corecta daca:
        1) elementele din lista de sume partiale >= 0
        2) ultimul element din lista de sume partiale = 0
        3) primul element din lista de solutie este 1 ( '(' )
        4) ultimul element din lista de solutie este -1 ( ')' )

        :param nr_total: nr total de elemente ale solutiei
        :param lista_solutii: lista in care se retine solutiile (liste)
        :return: None
        """
        pozitie = 0
        lista = [0] * nr_total
        lista[pozitie] = 1

        while pozitie != -1:
            if lista[pozitie] > 2:
                pozitie = pozitie - 1
                lista[pozitie] += 1
            else:
                if pozitie < nr_total - 1:
                    pozitie = pozitie + 1
                    lista[pozitie] = 1
                elif pozitie == nr_total - 1:
                    # decoding
                    new = Functii.bkt_decoding(lista)
                    if Functii.verificare_solutie(new):
                        lista_solutii.append(new)
                    lista[pozitie] += 1

    @staticmethod
    def main() -> None:
        numar = int(input('Introdu un numar: '))

        if numar % 2 == 0 and numar > 0:
            print('Recursiv:')
            lista = [0] * numar
            lista_solutii = []
            Functii.backtracking_recursiv(lista, 0, numar, lista_solutii)
            Functii.print_all_lists(lista_solutii)

            print('Iterativ:')
            lista_solutii = []
            Functii.backtracking_iterativ(numar, lista_solutii)
            Functii.print_all_lists(lista_solutii)
        else:
            print('Nu exista solutii pentru acest numar...')


if __name__ == '__main__':
    Functii.main()
