use FirmaDeTransport
GO

-- proceduri

-- 0 -> 1) modificarea tipului unei coloane
-- se va modifica in tabela Facturi tipul coloanei SumaPlata (int => float)
CREATE PROCEDURE ModificareTipColoane
AS
BEGIN
    ALTER TABLE Facturi
    ALTER COLUMN SumaPlata FLOAT;
END
GO

-- 1 -> 2) adaugare constrangere valoare implicita pentru un camp
-- pentru coloana SumaPlata din tabela Facturi, adaug valoarea implicita 0
CREATE PROCEDURE AdaugareConstrangereValoareImplicita
AS
BEGIN
    ALTER TABLE Facturi
    ADD CONSTRAINT DF_SumaPlata_Implicit DEFAULT 0 FOR SumaPlata;
END
GO

-- 2 -> 3) creeaza tabela noua
-- procedura va adauga tabela EvaluareSoferi
CREATE PROCEDURE CreeareTabelEvaluareSoferi
AS
BEGIN
	CREATE TABLE EvaluariSoferi (
    EvaluareID INT PRIMARY KEY IDENTITY,
    SoferCNP VARCHAR(13),
    DataEvaluare DATE NOT NULL,
    ScorPerformanta INT CHECK (ScorPerformanta BETWEEN 1 AND 10),
    Feedback VARCHAR(255)
);
END
GO

-- 3 -> 4) adauga un camp nou
-- procedura va adauga campul ComentariiSuplimentare
CREATE PROCEDURE AdaugaCampEvaluariSoferi
AS
BEGIN
    ALTER TABLE EvaluariSoferi
    ADD ComentariiSuplimentare VARCHAR(255);
END
GO

-- 4 -> 5) adauga o constrangere de cheie straina
-- procedura va adauga o constrangere de tip cheie straina in tabela EvaluariSoferi
CREATE PROCEDURE AdaugaCheieStrainaEvaluariSoferi
AS
BEGIN
    ALTER TABLE EvaluariSoferi
    ADD CONSTRAINT FK_EvaluariSoferi_Soferi
    FOREIGN KEY (SoferCNP) REFERENCES Soferi(CNPsofer);
END
GO


-- procedurile inverse

-- 5 -> 4) sterge constrangerea de tip cheie straina din tabela EvaluariSoferi
CREATE PROCEDURE EliminareCheieStrainaEvaluariSoferi
AS
BEGIN
    ALTER TABLE EvaluariSoferi
    DROP CONSTRAINT FK_EvaluariSoferi_Soferi;
END
GO

-- 4 -> 3) elimina coloana ComentariiSuplimentare din tabela EvaluariSoferi
CREATE PROCEDURE EliminareCampEvaluariSoferi
AS
BEGIN
    ALTER TABLE EvaluariSoferi
    DROP COLUMN ComentariiSuplimentare;
END
GO

-- 3 -> 2) sterge tabela EvaluariSoferi
CREATE PROCEDURE StergereTabelEvaluareSoferi
AS
BEGIN
    DROP TABLE IF EXISTS EvaluariSoferi;
END
GO

-- 2 -> 1) elimina constrangerea de valoare implicita pentru 
--         campul Salariu din tabela Soferi
CREATE PROCEDURE EliminareConstrangereValoareImplicita
AS
BEGIN
    ALTER TABLE Facturi
    DROP CONSTRAINT DF_SumaPlata_Implicit;
END
GO

-- 1 -> 0) revenire camp Salariu (de la FLOAT la INT)
CREATE PROCEDURE RevenireTipColoane
AS
BEGIN
    ALTER TABLE Facturi
    ALTER COLUMN SumaPlata INT;
END
GO
