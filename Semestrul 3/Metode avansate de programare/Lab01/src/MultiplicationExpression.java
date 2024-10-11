import java.util.ArrayList;

public class MultiplicationExpression extends ComplexExpression {
    public MultiplicationExpression(ArrayList<NumarComplex> nr) {
        super(nr);
    }

    @Override
    public void executeOneOperation() {
        if(this.numere.isEmpty()) return;

        this.rezultat = NumarComplex.inmultire(this.rezultat, this.numere.getFirst());
        this.numere.removeFirst();
    }
}
