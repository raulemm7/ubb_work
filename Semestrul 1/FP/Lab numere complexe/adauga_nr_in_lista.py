from citiri_si_afisari import citire_nr_complex


def creeare_nr_complex(mesaj_info):
    """
    :return: o lista de forma [parte_reala, parte_imaginara]
             care reprezinta un numar complex
    """
    nr_complex = []
    parte_reala, parte_imaginara = citire_nr_complex(mesaj_info)

    nr_complex.append(parte_reala)
    nr_complex.append(parte_imaginara)

    return nr_complex


# 1.1
def adauga_la_sfarsitul_listei(lista_cu_nr_complexe, nr_complex):
    """
    :param lista_cu_nr_complexe: -
    :param nr_complex: nr complex care va fi adaugat la lista
    :return: lista updatata
    preconditii: lista poate fi una vida
                 numarul complex sa fie unul valid:
                     o lista de forma [parte_reala, parte_imaginara]
    """
    lista_cu_nr_complexe.append(nr_complex)

    return lista_cu_nr_complexe


def test_adauga_la_sfarsitul_listei():
    assert adauga_la_sfarsitul_listei([], [1, 2]) == [[1, 2]]
    assert adauga_la_sfarsitul_listei([[1, 2]], [3, -4]) == [[1, 2], [3, -4]]


# 1.2
def inserare_la_o_pozitie_data(lista_cu_nr_complexe, nr_complex, index_value):
    """
    :param lista_cu_nr_complexe: -
    :param nr_complex: nr complex care va fi adaugat la o pozitie data
    :param index_value: pozitia la care va fi adaugart nr
    :return: lista updatata
    preconditii: lista poate fi una vida
                 numarul complex sa fie unul valid:
                     o lista de forma [parte_reala, parte_imaginara]
                 pozitia la care se adauga nr complex sa fie una valida:
                     0 <= index_value < lungimea listei
    """
    lista_cu_nr_complexe.insert(index_value, nr_complex)

    return lista_cu_nr_complexe


def test_inserare_la_o_pozitie_data():
    assert inserare_la_o_pozitie_data([], [1, 2], 0) == [[1, 2]]
    assert inserare_la_o_pozitie_data([[1, 2]], [3, -4], 1) == [[1, 2], [3, -4]]
