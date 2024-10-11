public class Main {
    public static void main(String[] args) {
        // instantiez un obiect de tip ExpressionParser cu care se poate
        // opera asupra stringurilor citite din linia de comanda
        ExpressionParser parser = new ExpressionParser(args);

        // daca expresia aferenta nu este valida, se afiseaza mesaj de eroare
        if(!parser.expresieValida()) {
            System.out.println("Expresie invalida!");
            return;
        }

        // in caz contrar, se afiseaza rezultatul
        System.out.println("Expresie valida!");
        System.out.println("Rezultat: " + parser.parseExpression().execute());
    }
}