import java.util.ArrayList;

public class ExpressionFactory {
    /**
     * folosind singleton design pattern, asiguram ca pentru aceasta clasa
     * se instantiaza un singur obiect pe toata durata executiei programului
     */
    private static final ExpressionFactory instance = new ExpressionFactory();

    private ExpressionFactory() {}

    public static ExpressionFactory getInstance() {
        return instance;
    }

    /**
     * creeaza o expresie
     * @param operator operatorul expresiei
     * @param numere lista cu numerele expresiei
     * @return obiect de tip ComplexExpression
     */
    public ComplexExpression createExpression(Operation operator, ArrayList<NumarComplex> numere) {
        switch (operator) {
            case ADDITION -> {
                return new AdditionExpression(numere);
            }
            case SUBTRACTION -> {
                return new SubtractExpression(numere);
            }
            case MULTIPLICATION -> {
                return new MultiplicationExpression(numere);
            }
            case DIVISION -> {
                return new DivisionExpression(numere);
            }
            default -> {
                return null;
            }
        }
    }
}
