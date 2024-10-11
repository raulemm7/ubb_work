import java.util.ArrayList;

public class AdditionExpression extends ComplexExpression{
    public AdditionExpression(ArrayList<NumarComplex> nr) {
        super(nr);
    }

    @Override
    public void executeOneOperation() {
        if(this.numere.isEmpty()) return;

        this.rezultat = NumarComplex.adunare(this.rezultat, this.numere.getFirst());
        this.numere.removeFirst();
    }
}
