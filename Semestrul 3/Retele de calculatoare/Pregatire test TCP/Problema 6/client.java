import java.io.*;
import java.net.*;

public class Main {
    /*
    Un client trimite unui server un sir de caractere si un caracter.
    Serverul va returna clientului toate pozitiile pe care caracterul primit se regaseste in sir.
     */

    private static final String SERVER_ADDRESS = "127.0.0.1";
    private static final int SERVER_PORT = 1278;

    public static void main(String[] args) {
        Socket socket = null;
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new InputStreamReader(System.in));
            socket = new Socket(SERVER_ADDRESS, SERVER_PORT);

            // Citesc sirul de caractere
            System.out.println("Sirul de caractere: ");
            String sir_caractere = reader.readLine();
            sir_caractere += '\0';

            System.out.println("Caracterul: ");
            char car = (char)reader.read();

            // Trimit sirul si caracterul catre server
            sendInfoToServer(sir_caractere, car, socket);

            // Primesc sirul cu pozitii
            receivePositions(socket);
        } catch (IOException e) {
            System.err.println("Caught exception: " + e.getMessage());
        } finally {
            closeStreams(socket, reader);
        }
    }

    private static void sendInfoToServer(String sir_caractere, char car, Socket socket) throws IOException {
        DataOutputStream socketOut = new DataOutputStream(socket.getOutputStream());
        socketOut.writeBytes(sir_caractere);
        socketOut.writeByte(car);
        socketOut.flush();
    }

    private static void receivePositions(Socket socket) throws IOException {
        DataInputStream socketIn = new DataInputStream(socket.getInputStream());

        var nrPozitii = socketIn.readUnsignedShort();
        System.out.println("[FROM SERVER] Sunt " + nrPozitii + "pozitii: ");
        for(int i = 0; i < nrPozitii; i++) {
            System.out.println(socketIn.readUnsignedShort());
        }
        System.out.println();
    }

    // Functie pentru închiderea conexiunii și a fluxurilor
    private static void closeStreams(Socket socket, BufferedReader reader) {
        if (socket != null) {
            try {
                socket.close();
            } catch (IOException e) {
                System.err.println("Could not close socket!");
            }
        }
        if (reader != null) {
            try {
                reader.close();
            } catch (IOException e) {
                System.err.println("Could not close reader!");
            }
        }
    }
}
