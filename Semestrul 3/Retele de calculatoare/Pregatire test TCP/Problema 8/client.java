import java.io.*;
import java.net.*;
import java.util.ArrayList;

public class Main {
    /*
    Un client trimite unui server doua siruri de numere.
    Serverul va returna clientului sirul de numere comune celor doua siruri primite.
     */

    private static final String SERVER_ADDRESS = "127.0.0.1";
    private static final int SERVER_PORT = 1244;
    private static final int UNSIGNED_SHORT_MIN_VALUE = 0;
    private static final int UNSIGNED_SHORT_MAX_VALUE = 65535;

    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
             Socket socket = new Socket(SERVER_ADDRESS, SERVER_PORT)){
            System.out.print("Primul sir de numere: ");
            var primulSir = reader.readLine();
            trimitereDate(socket, primulSir);

            System.out.print("Al doilea sir de numere: ");
            var aldoSir = reader.readLine();
            trimitereDate(socket, aldoSir);

            primesteAfiseazaDate(socket);
        }
        catch (IOException e) {
            System.out.println("Eroare la citire/afisare!");
        }
    }

    private static void primesteAfiseazaDate(Socket socket) throws IOException {
        DataInputStream in = new DataInputStream(socket.getInputStream());

        System.out.print("Numerele comune sunt: ");

        var nr = in.readShort();
        for(int i = 0 ; i < nr ; i++) {
            System.out.print(in.readShort() + " ");
        }

        in.close();
        System.out.println();
    }

    private static void trimitereDate(Socket socket, String line) throws IOException {
        DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());

        var parts = line.split(" ");

        var nrTotaleTrimise = parts.length;
        ArrayList<Integer> numere = new ArrayList<>();
        for(String part : parts) {
            var numar = Integer.parseInt(part);
            if(numar < UNSIGNED_SHORT_MIN_VALUE || numar > UNSIGNED_SHORT_MAX_VALUE) {
                System.out.println("Numarul " + numar + " nu e de tip short!");
                nrTotaleTrimise--;
            }
            else numere.add(numar);
        }

        dataOutputStream.writeShort(nrTotaleTrimise);
        for(int i = 0; i < nrTotaleTrimise; i++) {
            dataOutputStream.writeShort(numere.get(i));
        }
        dataOutputStream.flush();

        System.out.println("S au trimis " + nrTotaleTrimise + " numere din cele " + parts.length + " citite!");
    }
}
