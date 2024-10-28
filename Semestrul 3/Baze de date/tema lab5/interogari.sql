use FirmaDeTransport
go

-- interogari cu WHERE: 1, 3, 5, 7, 8, 10
-- interogari cu GROUP BY: 2, 4, 6, 8, 9
-- interogari cu DISTINCT: 1, 3
-- interogari cu HAVING: 2, 4, 9

-- 1
-- afiseaza numele si prenumele clientilor care au plasat comenzi catre Timisoara
SELECT DISTINCT Clienti.Nume, Clienti.Prenume
FROM Comenzi
JOIN Curse ON Comenzi.CursaID = Curse.CursaID
JOIN CurseRuteLeg ON Curse.CursaID = CurseRuteLeg.CursaID
JOIN Rute ON CurseRuteLeg.PunctPlecare = Rute.PunctPlecare AND CurseRuteLeg.PunctDestinatie = Rute.PunctDestinatie
JOIN Clienti ON Comenzi.ClientID = Clienti.ClientID
WHERE Rute.PunctDestinatie = 'Timisoara';

-- 2
-- afiseaza cursele care au transportat o greutate totala de marfa mai mare de 20 de tone
SELECT Curse.CursaID, Rute.PunctPlecare, Rute.PunctDestinatie, SUM(Marfuri.Greutate) AS TotalGreutate
FROM Curse
JOIN Marfuri ON Curse.TipMarfa = Marfuri.NumeMarfa
JOIN CurseRuteLeg ON Curse.CursaID = CurseRuteLeg.CursaID
JOIN Rute ON Rute.PunctDestinatie = CurseRuteLeg.PunctDestinatie AND Rute.PunctPlecare = CurseRuteLeg.PunctPlecare
GROUP BY Curse.CursaID, Rute.PunctPlecare, Rute.PunctDestinatie
HAVING SUM(Marfuri.Greutate) > 20;

-- 3
-- afiseaza toate destinatiile distincte catre care au fost efectuate comenzi
SELECT DISTINCT Rute.PunctDestinatie
FROM Comenzi
JOIN Curse ON Comenzi.CursaID = Curse.CursaID
JOIN CurseRuteLeg ON Curse.CursaID = CurseRuteLeg.CursaID
JOIN Rute ON CurseRuteLeg.PunctPlecare = Rute.PunctPlecare AND CurseRuteLeg.PunctDestinatie = Rute.PunctDestinatie;

-- 4
-- afiseaza numele si prenumele soferilor care au avut cel putin 2 curse
SELECT Soferi.Nume, Soferi.Prenume, COUNT(Curse.CursaID) AS NrCurse
FROM Soferi
JOIN Curse ON Soferi.CNPsofer = Curse.SoferCNP
JOIN CurseRuteLeg ON Curse.CursaID = CurseRuteLeg.CursaID
GROUP BY Soferi.Nume, Soferi.Prenume
HAVING COUNT(Curse.CursaID) > 1;

-- 5
-- afiseaza detaliile comenzilor (client, cursa, marfa) care includ marfa mai mare de 50 metri cubi
SELECT Comenzi.ComandaID, Clienti.Nume AS NumeClient, Clienti.Prenume AS PrenumeClient,
       Curse.CursaID, Marfuri.NumeMarfa, Marfuri.Volum
FROM Comenzi
JOIN Clienti ON Comenzi.ClientID = Clienti.ClientID
JOIN Curse ON Comenzi.CursaID = Curse.CursaID
JOIN Marfuri ON Curse.TipMarfa = Marfuri.NumeMarfa
WHERE Marfuri.Volum > 50;

-- 6
-- afiseaza totalul sumei de plata pentru fiecare client care are facturi cu statusul “efectuata”
SELECT Clienti.Nume, Clienti.Prenume, SUM(Facturi.SumaPlata) AS TotalPlata
FROM Comenzi
JOIN Clienti ON Comenzi.ClientID = Clienti.ClientID
JOIN Facturi ON Comenzi.FacturaID = Facturi.FacturaID
WHERE Facturi.StatusPlata = 'efectuata'
GROUP BY Clienti.Nume, Clienti.Prenume;

-- 7
-- afiseaza cursele care au parcurs o distanta mai mare de 300 km, impreuna cu informatiile despre punctul de plecare si destinatia lor
SELECT Curse.CursaID, Rute.PunctPlecare, Rute.PunctDestinatie, Curse.DataPlecare, Rute.DistantaKM
FROM Curse
JOIN CurseRuteLeg ON Curse.CursaID = CurseRuteLeg.CursaID
JOIN Rute ON CurseRuteLeg.PunctPlecare = Rute.PunctPlecare AND CurseRuteLeg.PunctDestinatie = Rute.PunctDestinatie
WHERE Rute.DistantaKM > 300;

-- 8
-- afiseaza cate comenzi a plasat fiecare client la o anumita destinatie
SELECT Clienti.Nume, Clienti.Prenume, Rute.PunctDestinatie, COUNT(Comenzi.ComandaID) AS NrComenzi
FROM Comenzi
JOIN Clienti ON Comenzi.ClientID = Clienti.ClientID
JOIN Curse ON Comenzi.CursaID = Curse.CursaID
JOIN CurseRuteLeg ON Curse.CursaID = CurseRuteLeg.CursaID
JOIN Rute ON CurseRuteLeg.PunctPlecare = Rute.PunctPlecare AND CurseRuteLeg.PunctDestinatie = Rute.PunctDestinatie
GROUP BY Clienti.Nume, Clienti.Prenume, Rute.PunctDestinatie;

-- 9
-- afiseaza marca și numarul de inmatriculare al camioanelor care au transportat marfa cu o greutate totala mai mare de 20 de tone
SELECT Camioane.Marca, Camioane.NrInmatriculare, SUM(Marfuri.Greutate) AS GreutateTotala
FROM Curse
JOIN Camioane ON Curse.CamionID = Camioane.CamionID
JOIN Marfuri ON Curse.TipMarfa = Marfuri.NumeMarfa
GROUP BY Camioane.Marca, Camioane.NrInmatriculare
HAVING SUM(Marfuri.Greutate) > 20;

-- 10
-- extrage detalii despre cursele realizate de soferi cu salarii de peste 3800, 
-- impreuna cu detalii despre camioanele si remorcile utilizate
SELECT Curse.CursaID, Soferi.Nume AS NumeSofer, Soferi.Prenume AS PrenumeSofer, 
       Camioane.Marca AS MarcaCamion, Camioane.NrInmatriculare AS NrCamion, Remorci.NrInmatriculare AS NrRemorca,
	   CurseRuteLeg.PunctPlecare AS PunctPlecare, CurseRuteLeg.PunctDestinatie AS PunctDestinatie
FROM Curse
JOIN Soferi ON Curse.SoferCNP = Soferi.CNPsofer
JOIN Camioane ON Curse.CamionID = Camioane.CamionID
JOIN Remorci ON Camioane.CamionID = Remorci.CamionID
JOIN CurseRuteLeg ON Curse.CursaID = CurseRuteLeg.CursaID
WHERE Soferi.Salariu > 3800;
