import java.util.ArrayList;

public class DivisionExpression extends ComplexExpression{
    public DivisionExpression(ArrayList<NumarComplex> nr) {
        super(nr);
    }

    @Override
    public void executeOneOperation() {
        if(this.numere.isEmpty()) return;

        this.rezultat = NumarComplex.impartire(this.rezultat, this.numere.getFirst());
        this.numere.removeFirst();
    }
}
