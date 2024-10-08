CREATE database FirmaDeTransport
go

use FirmaDeTransport
go

CREATE TABLE Camioane (
	CamionID INT PRIMARY KEY IDENTITY,
	NrInmatriculare VARCHAR(7) NOT NULL,
	Marca VARCHAR(12),
	Model VARCHAR(20),
	DataAchizitie DATE, 
	StatusCamion VARCHAR(25) NOT NULL  --ex: in folosinta, la service, la garaj etc.
);

CREATE TABLE Remorci (
	RemorcaID INT PRIMARY KEY IDENTITY,
	CamionID INT FOREIGN KEY REFERENCES Camioane(CamionID) NOT NULL,
	NrInmatriculare VARCHAR(7) NOT NULL, 
	MasaMaximaAdmisa INT, 
	VolumMaximAdmis INT,
	DataAchizitie DATE,
	StatusRemorca VARCHAR(25) NOT NULL
);

CREATE TABLE Soferi (
	CNPsofer INT PRIMARY KEY,
	Nume VARCHAR(30) NOT NULL, 
	Prenume VARCHAR(30) NOT NULL, 
	DataAngajarii DATE, 
	Salariu INT CHECK(Salariu >= 1500)
);

CREATE TABLE Marfuri (
	NumeMarfa VARCHAR(20) PRIMARY KEY, 
	DescriereMarfa VARCHAR(100), 
	Greutate INT CHECK(Greutate > 5 and Greutate < 35),  --exprimata in tone
	Volum INT CHECK(Volum < 80)                          --exprimat in m3
);

CREATE TABLE Curse (
	CursaID INT PRIMARY KEY IDENTITY,
	SoferCNP INT FOREIGN KEY REFERENCES Soferi(CNPsofer) NOT NULL,
	CamionID INT FOREIGN KEY REFERENCES Camioane(CamionID) NOT NULL,
	TipMarfa VARCHAR(20) FOREIGN KEY REFERENCES Marfuri(NumeMarfa) NOT NULL, 
	DataPlecare DATE, 
	OraPlecare TIME, 
);

CREATE TABLE Rute (
	PunctPlecare VARCHAR(25) NOT NULL, 
	PunctDestinatie VARCHAR(25) NOT NULL, 
	DistantaKM INT, 
	DurataEstimataParcurgere INT,
	PRIMARY KEY (PunctPlecare, PunctDestinatie)
);

CREATE TABLE CurseRuteLeg (
	CursaID INT FOREIGN KEY REFERENCES Curse(CursaID),
	PunctPlecare VARCHAR(25),
	PunctDestinatie VARCHAR(25),
	FOREIGN KEY (PunctPlecare, PunctDestinatie) REFERENCES Rute(PunctPlecare, PunctDestinatie),
	PRIMARY KEY (CursaID, PunctPlecare, PunctDestinatie)
);

CREATE TABLE CLIENTI (
	ClientID INT PRIMARY KEY IDENTITY, 
	Nume VARCHAR(25) NOT NULL, 
	Prenume VARCHAR(25) NOT NULL, 
	Telefon VARCHAR(14), 
	Email VARCHAR(40), 
	Adresa VARCHAR(80)
);

CREATE TABLE Comenzi (
	ComandaID INT PRIMARY KEY IDENTITY, 
	ClientID INT FOREIGN KEY REFERENCES Clienti(ClientID),
	CursaID INT FOREIGN KEY REFERENCES Curse(CursaID), 
	DataComanda DATE, 
	StatusComanda VARCHAR(25) NOT NULL     -- confirmata, preluata, spre destinatie, efectuata etc.
);

CREATE TABLE Facturi (
	FacturaID INT PRIMARY KEY IDENTITY,
	ComandaID INT FOREIGN KEY REFERENCES Comenzi(ComandaID), 
	DataEmitere DATE, 
	SumaPlata INT, 
	StatusPlata VARCHAR(25) NOT NULL       --ex: efectuata, in procesare etc.
);
