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

	IF @Versiune = @VersiuneBD
	BEGIN
		PRINT 'Esti deja la aceasta versiune!'
	END

    IF @Versiune > @VersiuneBD
    BEGIN
        -- creste versiunea
        WHILE @VersiuneBD < @Versiune
        BEGIN
            SET @VersiuneBD += 1;

            IF @VersiuneBD = 1
			BEGIN
				PRINT 'Upgrade la versiunea 1'
                EXEC dbo.ModificareTipColoane;
			END
            ELSE IF @VersiuneBD = 2
			BEGIN
				PRINT 'Upgrade la versiunea 2'
                EXEC AdaugareConstrangereValoareImplicita;
			END
            ELSE IF @VersiuneBD = 3
			BEGIN
				PRINT 'Upgrade la versiunea 3'
                EXEC CreeareTabelEvaluareSoferi;
			END
            ELSE IF @VersiuneBD = 4
			BEGIN
				PRINT 'Upgrade la versiunea 4'
                EXEC AdaugaCampEvaluariSoferi;
			END
            ELSE IF @VersiuneBD = 5
			BEGIN
				PRINT 'Upgrade la versiunea 5'
                EXEC AdaugaCheieStrainaEvaluariSoferi;
			END
        END;
    END
    ELSE
    BEGIN
        -- scade versiunea
        WHILE @VersiuneBD > @Versiune
        BEGIN
            SET @VersiuneBD -= 1;

            IF @VersiuneBD = 4
			BEGIN
				PRINT 'Downgrade la versiunea 4'
                EXEC EliminareCheieStrainaEvaluariSoferi;
			END
            ELSE IF @VersiuneBD = 3
			BEGIN
				PRINT 'Downgrade la versiunea 3'
                EXEC EliminareCampEvaluariSoferi;
			END
            ELSE IF @VersiuneBD = 2
			BEGIN
				PRINT 'Downgrade la versiunea 2'
                EXEC StergereTabelEvaluareSoferi;
			END
            ELSE IF @VersiuneBD = 1
			BEGIN
				PRINT 'Downgrade la versiunea 1'
                EXEC EliminareConstrangereValoareImplicita;
			END
            ELSE IF @VersiuneBD = 0
			BEGIN
				PRINT 'Downgrade la versiunea initiala (0)'
                EXEC RevenireTipColoane;
			END
        END;
    END;

    -- actualizare versiune curenta in tabel
    UPDATE VersiuneCurenta
    SET numar_versiune = @Versiune
    WHERE id_versiune = 1;
END;
GO
