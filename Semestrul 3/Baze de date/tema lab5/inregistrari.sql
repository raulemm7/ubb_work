-- adaug inregistrari in baza de date
use FirmaDeTransport
go

-- am facut ceva modificari
-- pentru campurile CNPsofer din tabela Soferi si
-- SoferCNP din tabela Curse am modificat
-- tipul la VARCHAR(13)
-- naiba mai stie cum am rulat codul
SELECT COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_NAME = 'Curse' AND COLUMN_NAME = 'SoferCNP';

Alter table Curse
Alter column SoferCNP VARCHAR(13) NOT NULL;

ALTER TABLE Soferi
DROP CONSTRAINT PK__Soferi__6CBE382C2282587B;  

ALTER TABLE Soferi
ADD CONSTRAINT PK__Soferi__6CBE382C2282587B PRIMARY KEY (CNPsofer);

ALTER TABLE Curse
ADD CONSTRAINT FK__Curse__SoferCNP__49C3F6B7 FOREIGN KEY (SoferCNP) REFERENCES Soferi(CNPsofer);


-- introduc in Facturi
-- resetez FacturiID la 0, fiind ca asa vreau
DBCC CHECKIDENT ('Facturi', RESEED, 0);

-- bag inregistrari
INSERT INTO Facturi (DataEmitere, SumaPlata, StatusPlata)
VALUES 
('2024-01-12', 1500, 'efectuata'),
('2024-01-14', 2000, 'in procesare'),
('2024-01-15', 2500, 'efectuata'),
('2024-01-16', 1800, 'in procesare'),
('2024-01-17', 2200, 'efectuata'),
('2024-01-18', 3000, 'in procesare'),
('2024-01-19', 2750, 'efectuata'),
('2024-02-02', 2400, 'efectuata'),
('2024-02-06', 6400, 'in procesare'), 
('2024-03-01', 4100, 'efectuata')

-- verific
SELECT * FROM Facturi


-- introduc in Clienti
DBCC CHECKIDENT ('Clienti', RESEED, 0);

INSERT INTO Clienti (Nume, Prenume, Telefon, Email, Adresa)
VALUES 
('Popescu', 'Ioana', '0722123456', 'ioana.popescu@gmail.com', 'Str. Libertatii, Nr. 10, Bucuresti'),
('Ionescu', 'George', '0733123456', 'george.ionescu@yahoo.com', 'Bd. Republicii, Nr. 5, Constanta'),
('Dumitrescu', 'Andrei', '0744123456', 'andrei.dumitrescu@gmail.com', 'Str. Mihai Viteazu, Nr. 22, Timisoara'),
('Stan', 'Alexandra', '0729123456', 'alexandra.stan@yahoo.com', 'Str. Lunii, Nr. 8, Cluj-Napoca'),
('Georgescu', 'Maria', '0728123456', 'maria.georgescu@gmail.com', 'Bd. Eroilor, Nr. 15, Brasov'),
('Popa', 'Ion', '0734123456', 'ion.popa@gmail.com', 'Str. Unirii, Nr. 45, Iasi'),
('Radu', 'Elena', '0723123456', 'elena.radu@yahoo.com', 'Bd. Victoriei, Nr. 9, Sibiu');

SELECT * FROM Clienti


-- introduc in Soferi
INSERT INTO Soferi (CNPsofer, Nume, Prenume, DataAngajarii, Salariu)
VALUES 
('1234567890123', 'Popescu', 'Ion', '2020-05-01', 3500),
('2345678901234', 'Ionescu', 'Maria', '2019-08-15', 3800),
('3456789012345', 'Dumitrescu', 'Vasile', '2021-02-20', 4000),
('4567890123456', 'Stan', 'Ana', '2022-11-25', 3600),
('5678901234567', 'Georgescu', 'Alexandru', '2021-06-05', 3900),
('6789012345678', 'Popa', 'Elena', '2020-03-12', 3400),
('7890123456789', 'Radu', 'Mihai', '2018-09-30', 4500);

SELECT * FROM Soferi


-- introduc in Marfuri
INSERT INTO Marfuri (NumeMarfa, DescriereMarfa, Greutate, Volum)
VALUES 
('Electrocasnice', 'Aparate de uz casnic', 10, 50),
('Mobilier', 'Mobilier de birou', 30, 75),
('Materiale', 'Materiale de construcții', 15, 40),
('Alimente', 'Produse alimentare perisabile', 8, 20),
('Textile', 'Imbracaminte si produse textile', 12, 45),
('Echipamente', 'Echipamente electronice', 20, 60),
('Auto', 'Piese auto', 25, 35);

SELECT * FROM Marfuri


-- introduc in Camioane
DBCC CHECKIDENT ('Camioane', RESEED, 0);

INSERT INTO Camioane (NrInmatriculare, Marca, Model, DataAchizitie, StatusCamion)
VALUES 
('B123ABC', 'Volvo', 'FH16', '2021-05-12', 'in folosinta'),
('B456DEF', 'Mercedes', 'Actros', '2020-03-15', 'in folosinta'),
('B789GHI', 'MAN', 'TGX', '2019-11-20', 'la service'),
('B111JKL', 'Scania', 'R450', '2018-07-18', 'la garaj'),
('B222MNO', 'DAF', 'XF', '2022-09-01', 'in folosinta'),
('B333PQR', 'Iveco', 'S-Way', '2019-12-05', 'la garaj'),
('B444STU', 'Renault', 'T High', '2023-01-25', 'in folosinta');

SELECT * FROM Camioane


-- introduc in Remorci
DBCC CHECKIDENT ('Remorci', RESEED, 0);

INSERT INTO Remorci (CamionID, NrInmatriculare, MasaMaximaAdmisa, VolumMaximAdmis, DataAchizitie, StatusRemorca)
VALUES 
(1, 'B555XYZ', 18000, 50, '2021-06-15', 'in folosinta'),
(2, 'B666ABC', 20000, 55, '2020-04-01', 'in folosinta'),
(3, 'B777DEF', 17500, 48, '2019-12-10', 'la service'),
(4, 'B888GHI', 19000, 52, '2018-08-22', 'la garaj'),
(5, 'B999JKL', 18500, 49, '2022-10-01', 'in folosinta'),
(6, 'B000MNO', 19500, 53, '2020-01-18', 'in folosinta'),
(7, 'B111PQR', 18000, 51, '2023-02-10', 'in folosinta');

SELECT * FROM Remorci


-- introduc in Rute
INSERT INTO Rute (PunctPlecare, PunctDestinatie, DistantaKM, DurataEstimataParcurgere)
VALUES 
('Bucuresti', 'Constanta', 225, 180),
('Cluj-Napoca', 'Timisoara', 320, 240),
('Iasi', 'Bacau', 135, 120),
('Brasov', 'Sibiu', 140, 120),
('Bucuresti', 'Ploiesti', 60, 50),
('Timisoara', 'Arad', 50, 45),
('Craiova', 'Drobeta-Turnu Severin', 110, 90),
('Oradea', 'Cluj-Napoca', 150, 130);

SELECT * FROM Rute


-- introduc in Curse
DBCC CHECKIDENT ('Curse', RESEED, 0);

INSERT INTO Curse (SoferCNP, CamionID, TipMarfa, DataPlecare, OraPlecare)
VALUES 
(1234567890123, 1, 'Electrocasnice', '2024-01-12', '08:30'),
(2345678901234, 2, 'Mobilier', '2024-01-14', '09:00'),
(3456789012345, 3, 'Materiale', '2024-01-15', '10:15'),
(4567890123456, 4, 'Alimente', '2024-01-16', '07:45'),
(5678901234567, 5, 'Textile', '2024-01-17', '11:00'),
(6789012345678, 6, 'Echipamente', '2024-01-18', '08:00'),
(7890123456789, 7, 'Auto', '2024-01-19', '12:30'),
('5678901234567', 5, 'Alimente', '2024-02-01', '05:00'), 
('4567890123456', 4, 'Auto', '2024-02-04', '07:00'),
('7890123456789', 7, 'Mobilier', '2024-02-09', '14:00');

SELECT * FROM Curse


-- introduc in CurseRuteLeg
INSERT INTO CurseRuteLeg (CursaID, PunctPlecare, PunctDestinatie)
VALUES 
(1, 'Bucuresti', 'Constanta'),
(2, 'Cluj-Napoca', 'Timisoara'),
(3, 'Iasi', 'Bacau'),
(4, 'Brasov', 'Sibiu'),
(5, 'Bucuresti', 'Ploiesti'),
(6, 'Timisoara', 'Arad'),
(7, 'Craiova', 'Drobeta-Turnu Severin'),
(8, 'Bucuresti', 'Constanta'),
(9, 'Cluj-Napoca', 'Timisoara'),
(10, 'Bucuresti', 'Ploiesti');

SELECT * FROM CurseRuteLeg


-- introduc in Comenzi
DBCC CHECKIDENT ('Comenzi', RESEED, 0);

INSERT INTO Comenzi (ClientID, CursaID, FacturaID, DataComanda, StatusComanda)
VALUES 
(1, 1, 1, '2024-01-12', 'confirmata'),
(2, 2, 2, '2024-01-13', 'preluata'),
(3, 3, 3, '2024-01-14', 'efectuata'),
(4, 4, 4, '2024-01-14', 'efectuata'),
(5, 5, 5, '2024-01-15', 'preluata'),
(6, 6, 6, '2024-01-16', 'spre destinatie'),
(7, 7, 7, '2024-01-17', 'confirmata'),
(2, 1, 1, '2024-01-11', 'spre destinatie'),
(3, 2, 2, '2024-01-12', 'efectuata'),
(4, 3, 3, '2024-01-13', 'spre destinatie'),
(5, 4, 4, '2024-01-15', 'confirmata'),
(6, 5, 5, '2024-01-16', 'preluata'),
(7, 6, 6, '2024-01-17', 'spre destinatie'),
(1, 7, 7, '2024-01-18', 'efectuata'),
(2, 8, 8, '2024-01-29', 'spre destinatie'),
(3, 9, 9, '2024-02-01', 'efectuata'),
(7, 10, 10, '2024-02-25', 'confirmata');

SELECT * FROM Comenzi


-- verific (asa, la vrajeala), ce am introdus in baza de date
SELECT a.Nume, a.Prenume, c.NrInmatriculare, c.Model
FROM Soferi a, Curse b, Camioane c
WHERE a.CNPsofer = b.SoferCNP and b.CamionID = c.CamionID
