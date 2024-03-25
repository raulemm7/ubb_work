from UI.ui_console import UIinput, UIoutput
from BUSSINES.afisari import AfisareInformatii
from BUSSINES.service import ServiceLista
from BUSSINES.service import ServiceCarti, ServiceClienti
from BUSSINES.service import ServiceTests
from REPOSITORY.storage import StorageInformation, FileStorage
from BUSSINES.random_data import ListaCartiRandom, ListaClientiRandom
from VALIDATOR.validation import Validator
from REPOSITORY.storage import StorageInformationTests, FileStorageTests
from DOMAIN.setters import DomainTests
from DOMAIN.setters import Clienti


class Main:
    @staticmethod
    def ruleaza_teste():
        Validator.Tests.run_validator_tests()

        storage_tests = StorageInformationTests()
        storage_tests.run_storage_tests()

        file_tests = FileStorageTests()
        file_tests.run_file_tests()

        ServiceTests.run_all_tests()
        DomainTests.run_tests()

    @staticmethod
    def main_app():
        Main.ruleaza_teste()

        lista_carti = StorageInformation()
        lista_clienti = StorageInformation()

        fisier_carti = FileStorage('IO_FILES/storage_carti.txt')
        fisier_clienti = FileStorage('IO_FILES/storage_clienti.txt')

        while True:
            UIoutput.meniu()

            comanda = UIinput.citire_comanda(10)

            if comanda == 1:
                UIoutput.meniu_adauga()

                comanda = UIinput.citire_comanda(2)
                if comanda == 1:
                    carte = UIinput.InputCarte()
                    carte = UIinput.InputCarte.creeare_carte(carte, lista_carti.get_len_lista(), lista_carti)
                    lista_carti.adaugare_in_lista(carte)
                    lista_carti.set_exemplare_valabile(carte.get_nr_inchirieri())

                elif comanda == 2:
                    client = UIinput.InputClient()
                    client = UIinput.InputClient.creeare_client(client, lista_clienti.get_len_lista(), lista_clienti)
                    lista_clienti.adaugare_in_lista(client)

            elif comanda == 2:
                UIoutput.meniu_sterge()

                comanda = UIinput.citire_comanda(2)
                if comanda == 1:
                    # verific daca am o lista nevida
                    if lista_carti.get_len_lista() == 0:
                        UIoutput.tipareste_mesaj('Nu exista informatii introduse!')
                    else:
                        id_obj = UIinput.citire_id(lista_carti.get_len_lista() - 1, 'cartii', 'o stergi: ')
                        lista_carti = ServiceLista.sterge_din_lista(lista_carti, id_obj)

                elif comanda == 2:
                    if lista_clienti.get_len_lista() == 0:
                        UIoutput.tipareste_mesaj('Nu exista informatii introduse!')
                    else:
                        id_obj = UIinput.citire_id(lista_clienti.get_len_lista() - 1, 'clientului', 'il stergi: ')
                        lista_clienti = ServiceLista.sterge_din_lista(lista_clienti, id_obj)

            elif comanda == 3:
                UIoutput.meniu_modifica()

                comanda = UIinput.citire_comanda(2)
                if comanda == 1:
                    UIoutput.meniu_modifica_carti()

                    if lista_carti.get_len_lista() == 0:
                        UIoutput.tipareste_mesaj('Nu exista informatii introduse!')
                    else:
                        comanda = UIinput.citire_comanda(3)
                        id_obj = UIinput.citire_id(lista_carti.get_len_lista() - 1, 'cartii', 'o modifici: ')
                        if comanda == 1:
                            new_titlu = UIinput.InputCarte.citire_titlu_carte(lista_carti)
                            lista_carti = ServiceCarti.modifica_titlu(lista_carti, id_obj, new_titlu)

                        elif comanda == 2:
                            new_autor = UIinput.InputCarte.citire_autor_carte()
                            lista_carti = ServiceCarti.modifica_autor(lista_carti, id_obj, new_autor)

                        elif comanda == 3:
                            new_descriere = UIinput.InputCarte.citire_descriere_carte()
                            lista_carti = ServiceCarti.modifica_descriere(lista_carti, id_obj, new_descriere)

                elif comanda == 2:
                    UIoutput.meniu_modifica_clienti()

                    if lista_clienti.get_len_lista() == 0:
                        UIoutput.tipareste_mesaj('Nu exista informatii introduse!')
                    else:
                        comanda = UIinput.citire_comanda(3)
                        id_obj = UIinput.citire_id(lista_clienti.get_len_lista() - 1, 'clientului', 'il modifici: ')
                        if comanda == 1:
                            new_nume = UIinput.InputClient.citire_nume_client()
                            lista_clienti = ServiceClienti.modifica_nume(lista_clienti, id_obj, new_nume)

                        elif comanda == 2:
                            new_prenume = UIinput.InputClient.citire_prenume_client()
                            lista_clienti = ServiceClienti.modifica_prenume(lista_clienti, id_obj, new_prenume)

                        elif comanda == 3:
                            new_cnp = UIinput.InputClient.citire_cnp_client()
                            lista_clienti = ServiceClienti.modifica_cnp(lista_clienti, id_obj, new_cnp)

            elif comanda == 4:
                UIoutput.meniu_cauta()

                comanda = UIinput.citire_comanda(2)
                if comanda == 1:
                    UIoutput.meniu_cauta_carte()

                    if lista_carti.get_len_lista() == 0:
                        UIoutput.tipareste_mesaj('Nu exista informatii introduse!')
                    else:
                        comanda = UIinput.citire_comanda(2)
                        if comanda == 1:
                            # caut carte dupa titlu
                            titlu = UIinput.InputCarte.citire_titlu_carte(lista_carti)
                            rezultat = ServiceCarti.cauta_dupa_titlu(lista_carti, titlu)

                            if rezultat == 0:
                                UIoutput.tipareste_mesaj('Nu exista carte inregistrata cu acest titlu!')
                            else:
                                UIoutput.afiseaza_informatii_carte(rezultat)

                        elif comanda == 2:
                            # caut carte dupa autor
                            autor = UIinput.InputCarte.citire_autor_carte()
                            rezultat = ServiceCarti.cauta_dupa_autor(lista_carti, autor, 0)

                            if rezultat == 0:
                                UIoutput.tipareste_mesaj('Nu exista carte inregistrata cu acest autor!')
                            else:
                                UIoutput.afiseaza_informatii_carte(rezultat)

                elif comanda == 2:
                    UIoutput.meniu_cauta_client()

                    if lista_clienti.get_len_lista() == 0:
                        UIoutput.tipareste_mesaj('Nu exista informatii inregistrate!')
                    else:
                        comanda = UIinput.citire_comanda(2)
                        if comanda == 1:
                            # caut dupa nume
                            nume = UIinput.InputClient.citire_nume_client()
                            rezultat = ServiceClienti.cauta_dupa_nume(lista_clienti, nume)

                            if rezultat == 0:
                                UIoutput.tipareste_mesaj('Nu exista client inregistrat cu acest nume!')
                            else:
                                UIoutput.afiseaza_informatii_client(rezultat)

                        elif comanda == 2:
                            # caut dupa prenume
                            prenume = UIinput.InputClient.citire_prenume_client()
                            rezultat = ServiceClienti.cauta_dupa_prenume(lista_clienti, prenume)

                            if rezultat == 0:
                                UIoutput.tipareste_mesaj('Nu exista client inregistrat cu acest prenume!')
                            else:
                                UIoutput.afiseaza_informatii_client(rezultat)

            elif comanda == 5:
                UIoutput.meniu_inc_ret_carte()

                comanda = UIinput.citire_comanda(2)
                if comanda == 1:
                    if lista_carti.get_exemplare_valabile() == 0:
                        UIoutput.tipareste_mesaj('Nu exista carti ce pot fi inchiriate!')
                    else:
                        # inchiriaza carte
                        # afisez lista de carti disponibile de inchiriat
                        AfisareInformatii.afisare_carti_valabile(lista_carti)
                        id_carte = UIinput.InputCarte.citire_id_carte_inchiriere(lista_carti.get_len_lista() - 1,
                                                                                 lista_carti)
                        carte_inchiriata = lista_carti.get_el_by_id(id_carte)
                        titlu = carte_inchiriata.get_titlu()

                        ok = False
                        id_client = 0
                        while not ok:
                            # afisez lista de clienti disponibili care doresc sa inchirieze cartea
                            AfisareInformatii.afisare_clienti(lista_clienti)
                            id_client = UIinput.InputClient.citire_id_client_inchiriaza(
                                lista_clienti.get_len_lista() - 1,
                                lista_clienti, titlu)
                            client = lista_clienti.get_el_by_id(id_client)

                            ok = ServiceClienti.cauta_carte_inchiriata(client, titlu)

                            if not ok:
                                UIoutput.tipareste_mesaj(
                                    'Introdu id-ul unui client care nu are inchiriata aceasta carte!')

                        # scad nr de carti disponibile
                        lista_carti = ServiceCarti.scade_carti_disponibile(lista_carti, id_carte)
                        lista_carti.set_exemplare_valabile(-1)

                        # adaug carte inchiriata la client
                        lista_clienti = ServiceClienti.adauga_carte_client(lista_clienti, id_client, titlu)

                elif comanda == 2:
                    if lista_clienti.get_len_lista() == 0:
                        UIoutput.tipareste_mesaj('Nu exista clienti ce pot returna carti!')
                    else:
                        # afisez clientii
                        AfisareInformatii.afisare_clienti(lista_clienti)

                        # introduc id client care poate returna carte
                        client = UIinput.InputClient.citire_id_client_returneaza(lista_clienti.get_len_lista() - 1,
                                                                                 lista_clienti)

                        # afisez cartile clientului
                        UIoutput.OutputClienti.afisare_carti_client(client)

                        # aleg o carte din lista disponibila
                        titlu_carte = UIinput.InputCarte.citire_id_carte_returnare(client)

                        # in lista de carti, mai adaug un exemplar la cartea cu titlul titlu_carte
                        lista_carti = ServiceCarti.adauga_carte_returnata(lista_carti, titlu_carte, 0)
                        lista_carti.set_exemplare_valabile(+1)

            elif comanda == 6:
                UIoutput.meniu_rapoarte()

                comanda = UIinput.citire_comanda(3)
                if comanda == 1:
                    # cea mai inchiriata carte
                    if lista_carti.get_len_lista() == 0:
                        UIoutput.tipareste_mesaj('Nu exista carti introduse!')
                    else:
                        carte_gasta = ServiceCarti.cea_mai_inchiriata_carte(lista_carti)

                        if carte_gasta.get_nr_exemplare_inchiriate() == 0:
                            UIoutput.tipareste_mesaj('Nu exista o carte care sa fie cea mai inchiriata!')
                        else:
                            AfisareInformatii.afisare_carte(carte_gasta)

                elif comanda == 2:
                    # aici am implementat MergeSort (lab 12)
                    lista_noua = StorageInformation()
                    ServiceLista.copiaza_lista(lista_clienti, lista_noua)
                    lista_noua = ServiceClienti.lista_cu_clienti_cu_carti(lista_noua)
                    ServiceClienti.Sort.merge_sort(lista_noua, 0, lista_noua.get_len_lista() - 1, Clienti.get_nume)
                    AfisareInformatii.afisare_clienti(lista_noua)

                elif comanda == 3:
                    # aici am implementat BingoSort (lab 12)
                    lista = ServiceClienti.cei_mai_activi_clienti_bingo_sort(lista_clienti, Clienti.get_nr_inchirieri)
                    AfisareInformatii.afisare_clienti(lista)

            elif comanda == 7:
                UIoutput.meniu_afisare_informatii()

                comanda = UIinput.citire_comanda(2)
                if comanda == 1:
                    AfisareInformatii.afisare_carti(lista_carti)
                elif comanda == 2:
                    AfisareInformatii.afisare_clienti(lista_clienti)

            elif comanda == 8:
                exit()

            elif comanda == 9:
                UIoutput.meniu_random()

                comanda = UIinput.citire_comanda(2)
                if comanda == 1:
                    # generez random carti
                    lista_carti = ListaCartiRandom.adauga_lista_carti(lista_carti)
                elif comanda == 2:
                    # generez clienti
                    lista_clienti = ListaClientiRandom.adauga_lista_clienti(lista_clienti)

            elif comanda == 10:
                # operatii cu fisier
                UIoutput.meniu_operatii_fisier()

                comanda = UIinput.citire_comanda(3)
                if comanda == 1:
                    pass
                    # introdu din fisier
                    UIoutput.alege_fisier()
                    comanda = UIinput.citire_comanda(2)

                    if comanda == 1:
                        lista_carti.load_from_file_carti(fisier_carti)
                    else:
                        lista_clienti.load_from_file_clienti(fisier_clienti)

                elif comanda == 2:
                    UIoutput.alege_fisier()
                    comanda = UIinput.citire_comanda(2)

                    if comanda == 1:
                        lista_carti.write_in_file_carti(fisier_carti)
                    else:
                        lista_clienti.write_in_file_clienti(fisier_clienti)

                elif comanda == 3:
                    UIoutput.alege_fisier()
                    comanda = UIinput.citire_comanda(2)

                    if comanda == 1:
                        fisier_carti.delete_all_data_from_file(fisier_carti.open_for_read())
                    else:
                        fisier_clienti.delete_all_data_from_file(fisier_clienti.open_for_read())

            UIoutput.tipareste_mesaj('Comanda efectuata cu succes!')


Main.main_app()
