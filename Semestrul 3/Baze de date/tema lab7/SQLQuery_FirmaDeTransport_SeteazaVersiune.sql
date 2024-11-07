use FirmaDeTransport
go

-- procedura care seteaza versiunea bazei de date
CREATE PROCEDURE SeteazaVersiune @Versiune INT
AS
BEGIN
    -- verificare versiune valida
    IF @Versiune < 0 OR @Versiune > 5
    BEGIN
        PRINT 'Versiune invalida';
        RETURN;
    END;

    -- obtine versiunea curenta din tabel
    DECLARE @VersiuneBD INT;
    SET @VersiuneBD = (SELECT numar_versiune FROM VersiuneCurenta WHERE id_versiune = 1);

    IF @Versiune > @VersiuneBD
    BEGIN
        -- creste versiunea
        WHILE @VersiuneBD < @Versiune
        BEGIN
            SET @VersiuneBD += 1;

            IF @VersiuneBD = 1
                EXEC dbo.ModificareTipColoane;
            ELSE IF @VersiuneBD = 2
                EXEC AdaugareConstrangereValoareImplicita;
            ELSE IF @VersiuneBD = 3
                EXEC CreeareTabelEvaluareSoferi;
            ELSE IF @VersiuneBD = 4
                EXEC AdaugaCampEvaluariSoferi;
            ELSE IF @VersiuneBD = 5
                EXEC AdaugaCheieStrainaEvaluariSoferi;
        END;
    END
    ELSE
    BEGIN
        -- scade versiunea
        WHILE @VersiuneBD > @Versiune
        BEGIN
            SET @VersiuneBD -= 1;

            IF @VersiuneBD = 4
                EXEC EliminareCheieStrainaEvaluariSoferi;
            ELSE IF @VersiuneBD = 3
                EXEC EliminareCampEvaluariSoferi;
            ELSE IF @VersiuneBD = 2
                EXEC StergereTabelEvaluareSoferi;
            ELSE IF @VersiuneBD = 1
                EXEC EliminareConstrangereValoareImplicita;
            ELSE IF @VersiuneBD = 0
                EXEC RevenireTipColoane;
        END;
    END;

    -- actualizare versiune curenta in tabel
    UPDATE VersiuneCurenta
    SET numar_versiune = @Versiune
    WHERE id_versiune = 1;
END;
GO
