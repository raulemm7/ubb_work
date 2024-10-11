import java.util.ArrayList;

public class ExpressionParser {
    private final String[] args;

    public ExpressionParser(String[] args) {
        this.args = args;
    }

    /**
     * verifica daca o expresie este valida sau nu
     */
    public boolean expresieValida() {
        if(this.args.length < 3 || this.args.length % 2 == 0) return false;

        // verificam numerele
        for(var i = 0; i < this.args.length; i += 2) {
            if(!numarValid(this.args[i])) return false;
        }

        // verificam operatorii
        var operator = args[1];
        for(var i = 1; i < this.args.length; i += 2) {
            if(!operatorValid(this.args[i]) || !operator.equals(args[i])) return false;
        }

        return true;
    }

    /**
     * parseaza o expresie si transforma argumentele
     * in obiecte de tip NumarComplex, puse intr-o lista
     */
    public ComplexExpression parseExpression() {
        if(!expresieValida()) return null;

        ArrayList<NumarComplex> numere = new ArrayList<>();
        for(var i = 0; i < this.args.length; i += 2) {
            numere.add(NumarComplex.fromString(this.args[i]));
        }

        Operation op = Operation.ADDITION;
        switch (this.args[1]) {
            case "-" -> op = Operation.SUBTRACTION;
            case "*" -> op = Operation.MULTIPLICATION;
            case "/" -> op = Operation.DIVISION;

        }

        return ExpressionFactory.getInstance().createExpression(op, numere);
    }

    /**
     * verifica daca un string poate reprezenta un nr complex
     * @param nr stringul pentru care se face verificarea
     * @return true || false
     */
    public boolean numarValid(String nr) {
        return NumarComplex.fromString(nr) != null;
    }

    /**
     * verifica daca un string poate reprezenta un operator matematic
     * @param op stringul pentru care se face verificarea
     * @return true || false
     */
    public boolean operatorValid(String op) {
        return op.equals("+") || op.equals("-") || op.equals("*") || op.equals("/");
    }
}
