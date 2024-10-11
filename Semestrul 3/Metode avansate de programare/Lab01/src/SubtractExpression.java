import java.util.ArrayList;

public class SubtractExpression extends ComplexExpression{
    public SubtractExpression(ArrayList<NumarComplex> nr) {
        super(nr);
    }

    @Override
    public void executeOneOperation(){
        if(this.numere.isEmpty()) return;

        this.rezultat = NumarComplex.scadere(this.rezultat, this.numere.getFirst());
        this.numere.removeFirst();
    }
}
