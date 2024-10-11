public class NumarComplex {
    // atributele unui numar complex
    private float parte_reala;
    private float parte_imaginara;

    public NumarComplex(float reala, float imaginara) {
        this.parte_reala = reala;
        this.parte_imaginara = imaginara;
    }

    // operatii pentru numere complexe
    public static NumarComplex adunare(NumarComplex a, NumarComplex b) {
        return new NumarComplex(a.parte_reala + b.parte_reala, a.parte_imaginara + b.parte_imaginara);
    }

    public static NumarComplex scadere(NumarComplex a, NumarComplex b) {
        return new NumarComplex(a.parte_reala - b.parte_reala, a.parte_imaginara - b.parte_imaginara);
    }

    public static NumarComplex inmultire(NumarComplex a, NumarComplex b) {
        var reala = a.parte_reala * b.parte_reala - a.parte_imaginara * b.parte_imaginara;
        var imaginara = a.parte_imaginara * b.parte_reala + a.parte_reala * b.parte_imaginara;
        return new NumarComplex(reala, imaginara);
    }

    public static NumarComplex conjugata(NumarComplex a) {
        return new NumarComplex(a.parte_reala, (-1) * a.parte_imaginara);
    }

    public static NumarComplex impartire(NumarComplex a, NumarComplex b) {
        NumarComplex numarator = NumarComplex.inmultire(a, NumarComplex.conjugata(b));
        NumarComplex numitor = NumarComplex.inmultire(b, NumarComplex.conjugata(b));

        return new NumarComplex(numarator.parte_reala / numitor.parte_reala,
                numarator.parte_imaginara / numitor.parte_imaginara);
    }

    /**
     * preia dintr-un string numarul complex aferent, daca este posibil
     * @param str stringul repr nr complex
     * @return obiect de tip NumarComplex daca stringul este formatat corect
     *          null, in caz contrar
     */
    public static NumarComplex fromString(String str) {
        int indexI = str.indexOf('i');

        // Daca b = 0
        if (indexI == -1) {
            try {
                float re = Float.parseFloat(str);
                return new NumarComplex(re, 0);
            } catch (NumberFormatException e) {
                return null;
            }
        }

        // Daca a = 0 si b = +-1
        if (str.equals("i")) return new NumarComplex(0, 1);
        if (str.equals("-i")) return new NumarComplex(0, -1);

        // Daca a = 0 si b != +-1
        int indexUltimSemn = Math.max(str.lastIndexOf('+'), str.lastIndexOf('-'));
        int indexSteluta = str.indexOf('*');
        if (indexUltimSemn == -1 || indexUltimSemn == 0) {
            String strIm = str.substring(0, indexSteluta);
            try {
                float im = Float.parseFloat(strIm);
                return new NumarComplex(0, im);
            } catch (NumberFormatException e) {
                return null;
            }
        }

        // Daca a != 0 si b = +-1
        if (indexUltimSemn + 1 == indexI) {
            int im;
            if (str.charAt(indexUltimSemn) == '-') im = -1;
            else im = 1;
            String strRe = str.substring(0, indexUltimSemn);
            try {
                float re = Float.parseFloat(strRe);
                return new NumarComplex(re, im);
            } catch (NumberFormatException e) {
                return null;
            }
        }

        // Daca coeficientul lui i nu e +-1 atunci apare obligatoriu steluta
        if (indexSteluta == -1) return null;

        String strIm = str.substring(indexUltimSemn, indexSteluta);
        String strRe = str.substring(0, indexUltimSemn);

        try {
            float im = Float.parseFloat(strIm);
            float re = Float.parseFloat(strRe);
            return new NumarComplex(re, im);
        } catch (NumberFormatException e) {
            return null;
        }
    }

    /**
     * suprascriere metoda toString a unui obiect de tip
     * NumarComplex
     */
    @Override
    public String toString() {
        return String.format("%f%+f*i", parte_reala, parte_imaginara);
    }
}
