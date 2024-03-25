# 2.1
def sterge_de_pe_pozitie(lista_cu_nr_complexe, index_value):
    """
    :param lista_cu_nr_complexe: -
    :param index_value: pozitia de unde se va sterge elementul
    :return: lista updatata
    preconditii: lista trebuie sa fie nevida
                 pozitia de la care se sterge nr complex sa fie una valida:
                     0 <= index_value < lungimea listei
    """
    lista_cu_nr_complexe.pop(index_value)

    return lista_cu_nr_complexe


def test_sterge_de_pe_pozitie():
    assert sterge_de_pe_pozitie([[1, 2]], 0) == []
    assert sterge_de_pe_pozitie([[1, 2], [3, -4]], 1) == [[1, 2]]


# 2.2
def sterge_interval_pozitii(lista_cu_nr_complexe, start_index, finish_index):
    """
    :param lista_cu_nr_complexe: -
    :param start_index: pozitia de inceput a subsecventei care va fi sterse
    :param finish_index: pozitia de sfarsit a subsecventei care va fi sterse
    :return: lista updatata
    preconditii: lista sa fie nevida
                 indicii de start si inceput a subsecventei  de elemente ce urmeaza a
                 fi stearsa sa fie valizi:
                     0 <= start_index <= finish_index < lungimea listei
    """
    nr_stergeri = finish_index - start_index + 1
    while nr_stergeri > 0:
        lista_cu_nr_complexe.pop(start_index)
        nr_stergeri -= 1

    return lista_cu_nr_complexe


def test_sterge_interval_pozitii():
    assert sterge_interval_pozitii([[1, 2], [3, -4]], 0, 1) == []
    assert sterge_interval_pozitii([[1, 2], [3, -4], [5, 6], [7, 8]], 2, 3) == [[1, 2], [3, -4]]
    assert sterge_interval_pozitii([[1, 2]], 0, 0) == []


# 2.3
def inlocuieste_aparitii(lista_cu_nr_complexe, nr_complex_de_inlocuit, nr_complex_inlocuitor):
    """
    :param lista_cu_nr_complexe: -
    :param nr_complex_de_inlocuit: nr complex care se va inlocui in lista
    :param nr_complex_inlocuitor: nr complex cu care se inlocuieste in lista
    :return: lista updatata
    preconditii: lista sa fie nevida
                 nr complexe declarate in antet sa fie liste de forma
                 [parte_reala, parte_imaginara]
    """
    for i in range(0, len(lista_cu_nr_complexe)):
        if lista_cu_nr_complexe[i] == nr_complex_de_inlocuit:
            lista_cu_nr_complexe[i] = nr_complex_inlocuitor

    return lista_cu_nr_complexe


def test_inlocuieste_aparitii():
    assert inlocuieste_aparitii([], [1, 2], [3, 4]) == []
    assert inlocuieste_aparitii([[3, 4], [2, 5], [3.0, 4.0]], [3, 4], [2, 3]) == [[2, 3], [2, 5], [2, 3]]
    assert inlocuieste_aparitii([[2, 3], [5, 6]], [2, 6], [7, 2]) == [[2, 3], [5, 6]]
