from UI.ui_console import UIoutput


class AfisareInformatii:
    @staticmethod
    def afisare_carte(_carte):
        print(_carte.get_id(), end=" ")
        print(" |  ", _carte.get_titlu(), end=" ")
        print(" |  ", _carte.get_autor(), end=" ")
        print(" |  ", _carte.get_descriere(), end=" ")
        print(" |  ", _carte.get_nr_inchirieri(), end=" ")
        print(" |  ", _carte.get_nr_total_de_exemplare(), end="\n")

    @staticmethod
    def afisare_carti(lista):
        if lista.get_len_lista() == 0:
            UIoutput.tipareste_mesaj('Nu exista informatii inregistrate!')
        else:
            UIoutput.tipareste_mesaj('ID carte  |  Titlu  |  Autor  |  Descriere  |  Nr de exemplare valabile  |  '
                                     'Nr total exemplare')
            for i in range(0, lista.get_len_lista()):
                el = lista.get_el_by_id(i)
                AfisareInformatii.afisare_carte(el)

    @staticmethod
    def afisare_client(client):
        print(client.get_id(), end=" ")
        print(" |  ", client.get_nume(), end=" ")
        print(" |  ", client.get_prenume(), end=" ")
        print(" |  ", client.get_cnp(), end=" ")
        print(" |  ", client.get_nr_inchirieri(), end=" ")
        print(" |  ", client.get_carti_inchiriate(), end="\n")

    @staticmethod
    def afisare_clienti(lista):
        if lista.get_len_lista() == 0:
            UIoutput.tipareste_mesaj('Nu exista informatii inregistrate!')
        else:
            UIoutput.tipareste_mesaj('ID client  |  Nume  |  Prenume  |  CNP  |  Nr. carti inchiriate  |  '
                                     'Carti inchiriate')
            for i in range(0, lista.get_len_lista()):
                el = lista.get_el_by_id(i)
                print(el.get_id(), end=" ")
                print(" |  ", el.get_nume(), end=" ")
                print(" |  ", el.get_prenume(), end=" ")
                print(" |  ", el.get_cnp(), end=" ")
                print(" |  ", el.get_nr_inchirieri(), end=" ")
                print(" |  ", el.get_carti_inchiriate(), end="\n")

    @staticmethod
    def afisare_carti_valabile(lista):
        UIoutput.tipareste_mesaj('ID carte  |  Titlu  |  Autor  |  Descriere  |  Nr de exemplare valabile')
        for i in range(0, lista.get_len_lista()):
            el = lista.get_el_by_id(i)

            if el.get_nr_inchirieri() > 0:
                print(el.get_id(), end=" ")
                print(" |  ", el.get_titlu(), end=" ")
                print(" |  ", el.get_autor(), end=" ")
                print(" |  ", el.get_descriere(), end=" ")
                print(" |  ", el.get_nr_inchirieri(), end="\n")
