import java.util.ArrayList;

public abstract class ComplexExpression {
    protected ArrayList<NumarComplex> numere;
    protected NumarComplex rezultat;

    public ComplexExpression(ArrayList<NumarComplex> numere) {
        this.numere = numere;

        if(!numere.isEmpty()){
            this.rezultat = numere.getFirst();
            numere.removeFirst();
        }
    }

    /**
     * @return rezultatul unei expresii valide
     */
    public NumarComplex execute() {
        while(!this.numere.isEmpty()) {
            executeOneOperation();
        }
        return this.rezultat;
    }

    /** executa o singuta operatie din expresia data */
    public abstract void executeOneOperation();

}
