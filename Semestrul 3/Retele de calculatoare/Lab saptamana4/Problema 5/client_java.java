import java.io.*;
import java.net.*;

public class Main {
    private static final String SERVER_ADDRESS = "127.0.0.1";
    private static final int SERVER_PORT = 1234;
    private static final int UNSIGNED_SHORT_MAX_VALUE = 65535;
    private static final int UNSIGNED_SHORT_MIN_VALUE = 0;

    public static void main(String[] args) {
        Socket socket = null;
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new InputStreamReader(System.in));
            socket = new Socket(SERVER_ADDRESS, SERVER_PORT);

            // Citesc numarul de la tastatură
            int numar = readUnsignedShort("Numar = ", reader);

            // Trimit numarul la server
            sendUnsignedShort(numar, socket);

            // Primesc sirul cu divizorii
            receiveDivisors(socket);
        } catch (IOException e) {
            System.err.println("Caught exception: " + e.getMessage());
        } finally {
            closeStreams(socket, reader);
        }
    }

    // Trimit unsigned short catre server
    private static void sendUnsignedShort(int numar, Socket socket) throws IOException {
        DataOutputStream socketOut = new DataOutputStream(socket.getOutputStream());
        socketOut.writeShort(numar);  // Trimit numarul
        socketOut.flush();
    }

    // Primesc de la server lista cu divizori
    private static void receiveDivisors(Socket socket) throws IOException {
        DataInputStream socketIn = new DataInputStream(socket.getInputStream());

        // Primesc numarul de divizori
        int nrDivizori = socketIn.readUnsignedShort();

        // Primesc divizorii si ii afisez
        System.out.print("[FROM SERVER] Sirul cu divizori: ");
        for (int i = 0; i < nrDivizori; i++) {
            int divizor = socketIn.readUnsignedShort();
            System.out.print(divizor + ", ");
        }
        System.out.println();
    }

    // Citesc unsigned short de la tastatura
    private static int readUnsignedShort(String message, BufferedReader reader) throws IOException {
        int unsignedShortNumber = 0;
        System.out.print(message);
        try {
            unsignedShortNumber = Integer.parseInt(reader.readLine());
            if (unsignedShortNumber < UNSIGNED_SHORT_MIN_VALUE || unsignedShortNumber > UNSIGNED_SHORT_MAX_VALUE) {
                throw new IllegalArgumentException("The given number must be unsigned short [0..65535]!");
            }
        } catch (NumberFormatException e) {
            System.err.println("The given input is not an integer!");
        }
        return unsignedShortNumber;
    }

    // inchid conexiunea
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
